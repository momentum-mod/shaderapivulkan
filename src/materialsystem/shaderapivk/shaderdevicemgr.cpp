#include "shaderdevicemgr.h"

bool CShaderDeviceMgr::Connect(CreateInterfaceFn factory)
{

	uint32_t count;
	vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr); //get number of extensions
	CUtlVector<VkExtensionProperties> fextensions(count);
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
	return nullptr;
}

InitReturnVal_t CShaderDeviceMgr::Init()
{
	InitAdapterInfo();

	return INIT_OK;
}

void CShaderDeviceMgr::Shutdown()
{
	
}

int CShaderDeviceMgr::GetAdapterCount() const
{
	return m_Adapters.Count();
}

void CShaderDeviceMgr::GetAdapterInfo(int nAdapter, MaterialAdapterInfo_t & info) const
{
	// index out of range checks are unnessecary :p never should happen
	info = m_Adapters[nAdapter].matdata;
}

bool CShaderDeviceMgr::GetRecommendedConfigurationInfo(int nAdapter, int nDXLevel, KeyValues * pConfiguration)
{
	return false;
}

int CShaderDeviceMgr::GetModeCount(int nAdapter) const
{
	return 0;
}

void CShaderDeviceMgr::GetModeInfo(ShaderDisplayMode_t * pInfo, int nAdapter, int nMode) const
{
}

void CShaderDeviceMgr::GetCurrentModeInfo(ShaderDisplayMode_t * pInfo, int nAdapter) const
{
}

bool CShaderDeviceMgr::SetAdapter(int nAdapter, int nFlags)
{
	return false;
}

CreateInterfaceFn CShaderDeviceMgr::SetMode(void * hWnd, int nAdapter, const ShaderDeviceInfo_t & mode)
{
	return CreateInterfaceFn();
}

void CShaderDeviceMgr::AddModeChangeCallback(ShaderModeChangeCallbackFunc_t func)
{
}

void CShaderDeviceMgr::RemoveModeChangeCallback(ShaderModeChangeCallbackFunc_t func)
{
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
		vkGetPhysicalDeviceProperties(devices[i], &properties);

		memset(&adapter, 0, sizeof(MyVkAdapterInfo));

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
