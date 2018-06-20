#include "shaderdevicemgr.h"
#include "shaderdevice.h"
#include "shaderapivk.h"
#include <tier2/tier2.h>
#include "shaderapi/ishaderutil.h"


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
        Warning("ShaderAPIDx10 was unable to access the required interfaces!\n");
        return false;
    }

    // NOTE! : Overbright is 1.0 so that Hammer will work properly with the white bumped and unbumped lightmaps.
    MathLib_Init(2.2f, 2.2f, 0.0f, 2.0f);


    // Initialize Vulkan
	uint32_t count;
	vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr); //get number of extensions
	CUtlVector<VkExtensionProperties> fextensions(count, count);
	vkEnumerateInstanceExtensionProperties(nullptr, &count, fextensions.begin()); //populate buffer
	CUtlVector<const char*> extensions;
	for (auto & extension : fextensions) {
		extensions.AddToTail(extension.extensionName);
	}

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
	
	return vkCreateInstance(&instanceCreateInfo, g_pAllocCallbacks, &m_hInstance) == VK_SUCCESS;
}

void CShaderDeviceMgr::Disconnect()
{
	vkDestroyInstance(m_hInstance, g_pAllocCallbacks);
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
	{
		g_pShaderDevice->ShutdownDevice();
		g_pShaderDevice = nullptr;
	}
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
	auto adapter = m_Adapters[nAdapter];
	return 0;
}

void CShaderDeviceMgr::GetModeInfo(ShaderDisplayMode_t * pInfo, int nAdapter, int nMode) const
{
}

void CShaderDeviceMgr::GetCurrentModeInfo(ShaderDisplayMode_t * pInfo, int nAdapter) const
{
	VkPhysicalDevice device = m_Adapters[nAdapter].device;


}

bool CShaderDeviceMgr::SetAdapter(int nAdapter, int nFlags)
{
	//deprecated
	return true;
}

CreateInterfaceFn CShaderDeviceMgr::SetMode(void * hWnd, int nAdapter, const ShaderDeviceInfo_t & mode)
{
	if (g_pShaderDevice)
	{
		g_pShaderDevice->ShutdownDevice();
	}

	g_pShaderDevice->InitDevice(hWnd, m_Adapters[nAdapter], mode);

	m_Mode = mode;

	return MyCreateInterface;
}

void CShaderDeviceMgr::AddModeChangeCallback(ShaderModeChangeCallbackFunc_t func)
{
}

void CShaderDeviceMgr::RemoveModeChangeCallback(ShaderModeChangeCallbackFunc_t func)
{
}

VkPhysicalDevice CShaderDeviceMgr::GetAdapter(int nIndex) const
{
	return m_Adapters[nIndex].device;
}

void CShaderDeviceMgr::InitAdapterInfo()
{
	m_Adapters.RemoveAll();

	uint32_t count = 0;
	vkEnumeratePhysicalDevices(m_hInstance, &count, nullptr);
	CUtlVector<VkPhysicalDevice> devices(count, count);
	vkEnumeratePhysicalDevices(m_hInstance, &count, devices.begin());

	VkPhysicalDeviceProperties properties;

	m_Adapters.SetSize(count);

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
