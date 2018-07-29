#include "shaderdevicemgr.h"
#include "shaderapivk.h"
#include <tier2/tier2.h>
#include "shaderapi/ishaderutil.h"
#include "shaderdevice.h"


//-----------------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------------
IShaderUtil* g_pShaderUtil;		// The main shader utility interface
static CShaderDeviceMgr g_ShaderDeviceMgrVk;
CShaderDeviceMgr* g_pShaderDeviceMgr = &g_ShaderDeviceMgrVk;

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CShaderDeviceMgr, IShaderDeviceMgr, SHADER_DEVICE_MGR_INTERFACE_VERSION, g_ShaderDeviceMgrVk);


//-----------------------------------------------------------------------------
// FIXME: Hack related to setting command-line values for convars. Remove!!!
//-----------------------------------------------------------------------------
class CShaderAPIConVarAccessor : public IConCommandBaseAccessor
{
public:
    virtual bool RegisterConCommandBase(ConCommandBase *pCommand)
    {
        // Link to engine's list instead
        g_pCVar->RegisterConCommand(pCommand);

        char const *pValue = g_pCVar->GetCommandLineValue(pCommand->GetName());
        if (pValue && !pCommand->IsCommand())
        {
            ((ConVar *) pCommand)->SetValue(pValue);
        }
        return true;
    }
};

static void InitShaderAPICVars()
{
    static CShaderAPIConVarAccessor g_ConVarAccessor;
    if (g_pCVar)
    {
        ConVar_Register(0, &g_ConVarAccessor);
    }
}

//-----------------------------------------------------------------------------
// Factory used to get at internal interfaces (used by shaderapi + shader dlls)
//-----------------------------------------------------------------------------
static CreateInterfaceFn s_TempFactory;
void *ShaderDeviceFactory(const char *pName, int *pReturnCode)
{
    if (pReturnCode)
    {
        *pReturnCode = IFACE_OK;
    }

    void *pInterface = s_TempFactory(pName, pReturnCode);
    if (pInterface)
        return pInterface;

    pInterface = Sys_GetFactoryThis()(pName, pReturnCode);
    if (pInterface)
        return pInterface;

    if (pReturnCode)
    {
        *pReturnCode = IFACE_FAILED;
    }
    return nullptr;
}

//-----------------------------------------------------------------------------
// CShaderDeviceMgr implemention
//-----------------------------------------------------------------------------
CShaderDeviceMgr::CShaderDeviceMgr()
{
    m_hInstance = VK_NULL_HANDLE;
}

CShaderDeviceMgr::~CShaderDeviceMgr()
{
}

bool CShaderDeviceMgr::Connect(CreateInterfaceFn factory)
{
    Assert(!g_pShaderDeviceMgr);

    s_TempFactory = factory;

    // Connection/convar registration
    CreateInterfaceFn actualFactory = ShaderDeviceFactory;
    ConnectTier1Libraries(&actualFactory, 1);
    InitShaderAPICVars();
    ConnectTier2Libraries(&actualFactory, 1);
    // ShaderUtil is actually defined in CMaterialSystem
    g_pShaderUtil = static_cast<IShaderUtil*>(ShaderDeviceFactory(SHADER_UTIL_INTERFACE_VERSION, nullptr));
    g_pShaderDeviceMgr = this;

    s_TempFactory = nullptr;

    if (!g_pShaderUtil || !g_pFullFileSystem || !g_pShaderDeviceMgr)
    {
        Warning("ShaderAPIVk was unable to access the required interfaces!\n");
        return false;
    }

    // NOTE! : Overbright is 1.0 so that Hammer will work properly with the white bumped and unbumped lightmaps.
    MathLib_Init(2.2f, 2.2f, 0.0f, 2.0f);


    // Initialize Vulkan
    CreateVkInstance();
	return true;
}

void CShaderDeviceMgr::Disconnect()
{
    CleanupVulkan();
}

void * CShaderDeviceMgr::QueryInterface(const char * pInterfaceName)
{
	if (!Q_stricmp(pInterfaceName, SHADER_DEVICE_MGR_INTERFACE_VERSION))
		return this;
	return nullptr;
}

InitReturnVal_t CShaderDeviceMgr::Init()
{
	InitAdapterInfo();

	return INIT_OK;
}

void CShaderDeviceMgr::Shutdown()
{
	if (g_pShaderDevice)
		g_pShaderDevice->ShutdownDevice();
}

int CShaderDeviceMgr::GetAdapterCount() const
{
	return m_Adapters.Count();
}

void CShaderDeviceMgr::GetAdapterInfo(int nAdapter, MaterialAdapterInfo_t & info) const
{
	// index out of range checks are unnecessary :p never should happen
	info = m_Adapters[nAdapter].matdata;
}

bool CShaderDeviceMgr::GetRecommendedConfigurationInfo(int nAdapter, int nDXLevel, KeyValues * pConfiguration)
{
	return true;
}

int CShaderDeviceMgr::GetModeCount(int nAdapter) const
{
	return 1;
}

void CShaderDeviceMgr::GetModeInfo(ShaderDisplayMode_t * pInfo, int nAdapter, int nMode) const
{
	*pInfo = m_Adapters[nAdapter].shaderMode;
}

void CShaderDeviceMgr::GetCurrentModeInfo(ShaderDisplayMode_t * pInfo, int nAdapter) const
{
	*pInfo = m_Adapters[nAdapter].shaderMode;
}

bool CShaderDeviceMgr::SetAdapter(int nAdapter, int nFlags)
{
	m_nCurAdapter = nAdapter;
	return true;
}

CreateInterfaceFn CShaderDeviceMgr::SetMode(void * hWnd, int nAdapter, const ShaderDeviceInfo_t & mode)
{
	if (g_pShaderDevice)
	{
		g_pShaderDevice->ShutdownDevice();
	}

    if (m_hSurface != VK_NULL_HANDLE)
    {
        DestroyVkSurface();
    }

    m_hWnd = hWnd;

    CreateVkSurface();

	g_pShaderDevice->InitDevice(m_hSurface, m_Adapters[nAdapter], mode);

	m_Mode = mode;

	return MyCreateInterface;
}

void CShaderDeviceMgr::AddModeChangeCallback(ShaderModeChangeCallbackFunc_t func)
{
}

void CShaderDeviceMgr::RemoveModeChangeCallback(ShaderModeChangeCallbackFunc_t func)
{
}

void CShaderDeviceMgr::CreateVkInstance()
{
    uint32_t count;
    vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr); //get number of extensions
    CUtlVector<VkExtensionProperties> fextensions(count, count);
    vkEnumerateInstanceExtensionProperties(nullptr, &count, fextensions.begin()); //populate buffer
    CUtlVector<const char*> extensions;
    for (auto & extension : fextensions)
        extensions.AddToTail(extension.extensionName);
  
    VkApplicationInfo appInfo =
    {
        VK_STRUCTURE_TYPE_APPLICATION_INFO,
        nullptr,
        "shaderapivulkan",
        VK_MAKE_VERSION(0,0,1),
        "Source Engine",
        VK_MAKE_VERSION(1,0,0)
    };

    VkInstanceCreateInfo instanceCreateInfo =
    {
        VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        nullptr,
        0,
        &appInfo,
        0,
        nullptr,
        count,
        extensions.begin()
    };

    vkCheck(vkCreateInstance(&instanceCreateInfo, g_pAllocCallbacks, &m_hInstance));
}

void CShaderDeviceMgr::CreateVkSurface()
{
    // MOM_TODO: Make this platform dependent
    VkWin32SurfaceCreateInfoKHR createInfo = {VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR};
    createInfo.hwnd = (HWND) m_hWnd;
    // GetModuleHandle should be platform independent (defined in interface.h) on Linux/mac
    createInfo.hinstance = GetModuleHandle(nullptr);

	vkCheck(vkCreateWin32SurfaceKHR(m_hInstance, &createInfo, g_pAllocCallbacks, &m_hSurface));
}

void CShaderDeviceMgr::CleanupVulkan()
{

    /*for (int i = 0; i < NUM_FRAME_DATA; ++i)
    {
        idImage::EmptyGarbage();
    }

    // Detroy Frame Buffers
    DestroyFrameBuffers();

    // Destroy Pipeline Cache
    vkDestroyPipelineCache(vkcontext.device, vkcontext.pipelineCache, NULL);

    // Destroy Render Pass
    vkDestroyRenderPass(vkcontext.device, vkcontext.renderPass, NULL);

    // Destroy Render Targets
    DestroyRenderTargets();

    // Destroy Swap Chain
    DestroySwapChain();

    // Stop the Staging Manager
    stagingManager.Shutdown();

    // Destroy Command Buffer
    vkFreeCommandBuffers(vkcontext.device, m_commandPool, NUM_FRAME_DATA, m_commandBuffers.Ptr());
    for (int i = 0; i < NUM_FRAME_DATA; ++i)
    {
        vkDestroyFence(vkcontext.device, m_commandBufferFences[i], NULL);
    }

    // Destroy Command Pool
    vkDestroyCommandPool(vkcontext.device, m_commandPool, NULL);

    // Destroy Query Pools
    for (int i = 0; i < NUM_FRAME_DATA; ++i)
    {
        vkDestroyQueryPool(vkcontext.device, m_queryPools[i], NULL);
    }

    // Destroy Semaphores
    for (int i = 0; i < NUM_FRAME_DATA; ++i)
    {
        vkDestroySemaphore(vkcontext.device, m_acquireSemaphores[i], NULL);
        vkDestroySemaphore(vkcontext.device, m_renderCompleteSemaphores[i], NULL);
    }

    // Destroy Debug Callback
    if (r_vkEnableValidationLayers.GetBool())
    {
        DestroyDebugReportCallback(m_instance);
    }

    // Dump all our memory
#if defined( ID_USE_AMD_ALLOCATOR )
    vmaDestroyAllocator(vmaAllocator);
#else
    vulkanAllocator.Shutdown();
#endif*/

    // Destroy Logical Device
    //vkDestroyDevice(g_p, NULL);
    if (g_pShaderDevice)
        g_pShaderDevice->ShutdownDevice();

    // Destroy Surface
    DestroyVkSurface();

    // Destroy the Instance
    vkDestroyInstance(m_hInstance, g_pAllocCallbacks);
}

void CShaderDeviceMgr::DestroyVkSurface()
{
    vkDestroySurfaceKHR(m_hInstance, m_hSurface, g_pAllocCallbacks);
}

VkPhysicalDevice CShaderDeviceMgr::GetAdapter(int nIndex) const
{
	return m_Adapters[nIndex].device;
}

void CShaderDeviceMgr::InitAdapterInfo()
{
	m_Adapters.RemoveAll();

	uint32_t count = 0;
	vkCheck(vkEnumeratePhysicalDevices(m_hInstance, &count, nullptr));
	CUtlVector<VkPhysicalDevice> devices(count, count);
	vkCheck(vkEnumeratePhysicalDevices(m_hInstance, &count, devices.begin()));

	m_Adapters.SetSize(count);

	CUtlVector<VkFormatProperties> formatProperties;

	for (int i = 0; i < count; i++)
	{
		auto& adapter = m_Adapters[i];
		memset(&adapter, 0, sizeof(MyVkAdapterInfo));

		vkGetPhysicalDeviceProperties(devices[i], &adapter.props);
		auto& properties = adapter.props;

		adapter.device = devices[i];
		adapter.matdata.m_DeviceID = properties.deviceID;
		adapter.matdata.m_nDriverVersionHigh = properties.driverVersion >> 16;
		adapter.matdata.m_nDriverVersionLow = properties.driverVersion & 0xFFFF;
		adapter.matdata.m_nDXSupportLevel = adapter.matdata.m_nMaxDXSupportLevel = 0;
		adapter.matdata.m_VendorID = properties.vendorID;
		strcpy(adapter.matdata.m_pDriverName, "(not retrieved)");
		adapter.matdata.m_SubSysID = -1;

		adapter.shaderMode.m_nWidth = adapter.props.limits.maxFramebufferWidth;
		adapter.shaderMode.m_nHeight = adapter.props.limits.maxFramebufferHeight;
		adapter.shaderMode.m_Format = ImageFormat::IMAGE_FORMAT_UNKNOWN;
		adapter.shaderMode.m_nRefreshRateNumerator = 1;
		adapter.shaderMode.m_nRefreshRateDenominator = 0;
		adapter.shaderMode.m_nVersion = 1;
	}

}

VkInstance CShaderDeviceMgr::GetInstance()
{
	return m_hInstance;
}

void * CShaderDeviceMgr::MyCreateInterface(const char * pInterfaceName, int * pReturnCode)
{
	if (pReturnCode)
		*pReturnCode = IFACE_OK;
	if (!Q_stricmp(pInterfaceName, SHADER_DEVICE_INTERFACE_VERSION))
		return dynamic_cast< IShaderDevice* >(g_pShaderDevice);
	if (!Q_stricmp(pInterfaceName, SHADERAPI_INTERFACE_VERSION))
		return dynamic_cast< IShaderAPI* >(g_pShaderAPI);
	//if (!Q_stricmp(pInterfaceName, SHADERSHADOW_INTERFACE_VERSION))
	//	return static_cast< IShaderShadow* >(g_pShaderShadow);
	if (pReturnCode)
		*pReturnCode = IFACE_FAILED;
	return nullptr;
}
