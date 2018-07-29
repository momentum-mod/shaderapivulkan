#include "shaderdevice.h"
#include "vulkanimpl.h"
#include "shaderdevicemgr.h"


static CShaderDevice g_ShaderDeviceVk;
CShaderDevice *g_pShaderDevice = &g_ShaderDeviceVk;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CShaderDevice, IShaderDevice,
                                  SHADER_DEVICE_INTERFACE_VERSION, g_ShaderDeviceVk)


void GetQueueFamily(int& queueFamily, VkPhysicalDevice device)
{
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	CUtlVector<VkQueueFamilyProperties> queueFamilies;
	queueFamilies.SetSize(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.begin());

	queueFamily = -1;
	for (auto& family : queueFamilies)
	{
		if (family.queueFlags & VK_QUEUE_GRAPHICS_BIT && family.queueCount > queueFamily)
			queueFamily = family.queueCount;
	}
}

CShaderDevice::CShaderDevice()
{
    m_Device = VK_NULL_HANDLE;
    m_Queue = VK_NULL_HANDLE;
}

CShaderDevice::~CShaderDevice()
{
}

void CShaderDevice::InitDevice(VkSurfaceKHR surface, MyVkAdapterInfo& adapterInfo, const ShaderDeviceInfo_t& creationInfo)
{
    int queueFamily;
    GetQueueFamily(queueFamily, adapterInfo.device);

    VkPhysicalDeviceFeatures features;
    vkGetPhysicalDeviceFeatures(adapterInfo.device, &features);

    float queuePriority = 1.0f;
    VkDeviceQueueCreateInfo queueCreateInfo = //{VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO};
    
    {
        VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        nullptr,
        0,
        queueFamily,
        1,
        &queuePriority
    };

    VkDeviceCreateInfo createInfo =
    {
        VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        nullptr,
        0,
        1,
        &queueCreateInfo,
        0,
        nullptr,
        0,
        nullptr,
        &features
    };

    VkResult result = vkCreateDevice(adapterInfo.device, &createInfo, g_pAllocCallbacks, &m_Device);

    if (result != VK_SUCCESS)
    {

    }

    

    vkGetDeviceQueue(m_Device, 0, 0, &m_Queue);
}

void CShaderDevice::ReleaseResources()
{
}

void CShaderDevice::ReacquireResources()
{
}

ImageFormat CShaderDevice::GetBackBufferFormat() const
{
	return _backBufferFormat;
}

void CShaderDevice::GetBackBufferDimensions(int & width, int & height) const
{
	width = _backBufferSize[0];
	height = _backBufferSize[1];
}

int CShaderDevice::GetCurrentAdapter() const
{
	return 0;
}

bool CShaderDevice::IsUsingGraphics() const
{
	return false;
}

void CShaderDevice::SpewDriverInfo() const
{
}

int CShaderDevice::StencilBufferBits() const
{
	return 0;
}

bool CShaderDevice::IsAAEnabled() const
{
	return false;
}

void CShaderDevice::Present()
{
}

void CShaderDevice::GetWindowSize(int & nWidth, int & nHeight) const
{
}

void CShaderDevice::SetHardwareGammaRamp(float fGamma, float fGammaTVRangeMin, float fGammaTVRangeMax, float fGammaTVExponent, bool bTVEnabled)
{
}

bool CShaderDevice::AddView(void * hWnd)
{
	return false;
}

void CShaderDevice::RemoveView(void * hWnd)
{
}

void CShaderDevice::SetView(void * hWnd)
{
}

IShaderBuffer * CShaderDevice::CompileShader(const char * pProgram, size_t nBufLen, const char * pShaderVersion)
{
	return nullptr;
}

VertexShaderHandle_t CShaderDevice::CreateVertexShader(IShaderBuffer * pShaderBuffer)
{
	return VertexShaderHandle_t();
}

void CShaderDevice::DestroyVertexShader(VertexShaderHandle_t hShader)
{
}

GeometryShaderHandle_t CShaderDevice::CreateGeometryShader(IShaderBuffer * pShaderBuffer)
{
	return GeometryShaderHandle_t();
}

void CShaderDevice::DestroyGeometryShader(GeometryShaderHandle_t hShader)
{
}

PixelShaderHandle_t CShaderDevice::CreatePixelShader(IShaderBuffer * pShaderBuffer)
{
	return PixelShaderHandle_t();
}

void CShaderDevice::DestroyPixelShader(PixelShaderHandle_t hShader)
{
}

VertexShaderHandle_t CShaderDevice::CreateVertexShader(const char * pProgram, size_t nBufLen, const char * pShaderVersion)
{
	return VertexShaderHandle_t();
}

VertexShaderHandle_t CShaderDevice::CreateVertexShader(CUtlBuffer & buf, const char * pShaderVersion)
{
	return VertexShaderHandle_t();
}

GeometryShaderHandle_t CShaderDevice::CreateGeometryShader(const char * pProgram, size_t nBufLen, const char * pShaderVersion)
{
	return GeometryShaderHandle_t();
}

GeometryShaderHandle_t CShaderDevice::CreateGeometryShader(CUtlBuffer & buf, const char * pShaderVersion)
{
	return GeometryShaderHandle_t();
}

PixelShaderHandle_t CShaderDevice::CreatePixelShader(const char * pProgram, size_t nBufLen, const char * pShaderVersion)
{
	return PixelShaderHandle_t();
}

PixelShaderHandle_t CShaderDevice::CreatePixelShader(CUtlBuffer & buf, const char * pShaderVersion)
{
	return PixelShaderHandle_t();
}

IMesh * CShaderDevice::CreateStaticMesh(VertexFormat_t vertexFormat, const char * pTextureBudgetGroup, IMaterial * pMaterial)
{
	return nullptr;
}

void CShaderDevice::DestroyStaticMesh(IMesh * mesh)
{
}

IVertexBuffer * CShaderDevice::CreateVertexBuffer(ShaderBufferType_t type, VertexFormat_t fmt, int nVertexCount, const char * pBudgetGroup)
{
	return nullptr;
}

void CShaderDevice::DestroyVertexBuffer(IVertexBuffer * pVertexBuffer)
{
}

IIndexBuffer * CShaderDevice::CreateIndexBuffer(ShaderBufferType_t bufferType, MaterialIndexFormat_t fmt, int nIndexCount, const char * pBudgetGroup)
{
	return nullptr;
}

void CShaderDevice::DestroyIndexBuffer(IIndexBuffer * pIndexBuffer)
{
}

IVertexBuffer * CShaderDevice::GetDynamicVertexBuffer(int nStreamID, VertexFormat_t vertexFormat, bool bBuffered)
{
	return nullptr;
}

IIndexBuffer * CShaderDevice::GetDynamicIndexBuffer(MaterialIndexFormat_t fmt, bool bBuffered)
{
	return nullptr;
}

void CShaderDevice::EnableNonInteractiveMode(MaterialNonInteractiveMode_t mode, ShaderNonInteractiveInfo_t * pInfo)
{
}

void CShaderDevice::RefreshFrontBufferNonInteractive()
{
}

void CShaderDevice::HandleThreadEvent(uint32 threadEvent)
{
}

char * CShaderDevice::GetDisplayDeviceName()
{
	return "(unspecified)";
}

void CShaderDevice::ShutdownDevice()
{
	vkDestroyDevice(m_Device, g_pAllocCallbacks);
}

VkDevice CShaderDevice::GetDevice()
{
	return m_Device;
}
