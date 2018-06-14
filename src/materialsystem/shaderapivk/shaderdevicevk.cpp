#include "shaderdevicevk.h"

#pragma region Device Manager

VkDeviceWrapper * gVkDeviceWrapper()
{
	return nullptr;
}

bool CShaderDeviceMgrVk::ComputeCapsFromD3D(HardwareCaps_t * pCaps, int nAdapter)
{
	return false;
}

void CShaderDeviceMgrVk::ForceCapsToDXLevel(HardwareCaps_t * pCaps, int nDxLevel, const HardwareCaps_t & actualCaps)
{
}

bool CShaderDeviceMgrVk::ValidateMode(int nAdapter, const ShaderDeviceInfo_t & info) const
{
	return false;
}

int CShaderDeviceMgrVk::GetVidMemBytes(int nAdapter) const
{
	return 0;
}

bool CShaderDeviceMgrVk::DetermineHardwareCaps()
{
	return false;
}

void CShaderDeviceMgrVk::InitAdapterInfo()
{
}

void CShaderDeviceMgrVk::CheckNormalCompressionSupport(HardwareCaps_t * pCaps, int nAdapter)
{
}

void CShaderDeviceMgrVk::CheckBorderColorSupport(HardwareCaps_t * pCaps, int nAdapter)
{
}

void CShaderDeviceMgrVk::CheckVendorDependentShadowMappingSupport(HardwareCaps_t * pCaps, int nAdapter)
{
}

void CShaderDeviceMgrVk::CheckVendorDependentAlphaToCoverage(HardwareCaps_t * pCaps, int nAdapter)
{
}

CShaderDeviceMgrVk::CShaderDeviceMgrVk()
{
}

CShaderDeviceMgrVk::~CShaderDeviceMgrVk()
{
}

bool CShaderDeviceMgrVk::Connect(CreateInterfaceFn factory)
{
	return false;
}

void CShaderDeviceMgrVk::Disconnect()
{
}

InitReturnVal_t CShaderDeviceMgrVk::Init()
{
	return InitReturnVal_t();
}

void CShaderDeviceMgrVk::Shutdown()
{
}

int CShaderDeviceMgrVk::GetAdapterCount() const
{
	return 0;
}

void CShaderDeviceMgrVk::GetAdapterInfo(int adapter, MaterialAdapterInfo_t & info) const
{
}

int CShaderDeviceMgrVk::GetModeCount(int nAdapter) const
{
	return 0;
}

void CShaderDeviceMgrVk::GetModeInfo(ShaderDisplayMode_t * pInfo, int nAdapter, int mode) const
{
}

void CShaderDeviceMgrVk::GetCurrentModeInfo(ShaderDisplayMode_t * pInfo, int nAdapter) const
{
}

bool CShaderDeviceMgrVk::SetAdapter(int nAdapter, int nFlags)
{
	return false;
}

CreateInterfaceFn CShaderDeviceMgrVk::SetMode(void * hWnd, int nAdapter, const ShaderDeviceInfo_t & mode)
{
	return CreateInterfaceFn();
}

#pragma endregion

#pragma region Device

bool CShaderDeviceVk::CreateVkDevice(void * pHWnd, int nAdapter, const ShaderDeviceInfo_t & info)
{
	return false;
}

VkPhysicalDevice CShaderDeviceVk::InvokeCreateDevice(void * hWnd, int nAdapter, uint32_t deviceCreationFlags)
{
	return VkPhysicalDevice();
}

void CShaderDeviceVk::DetectQuerySupport(VkDevice pD3DDevice)
{
}

void CShaderDeviceVk::SetPresentParameters(void * hWnd, int nAdapter, const ShaderDeviceInfo_t & info)
{
}

bool CShaderDeviceVk::IsActive() const
{
	return false;
}

bool CShaderDeviceVk::TryDeviceReset()
{
	return false;
}

void CShaderDeviceVk::MarkDeviceLost()
{
}

void CShaderDeviceVk::CheckDeviceLost(bool bOtherAppInitializing)
{
}

bool CShaderDeviceVk::ResizeWindow(const ShaderDeviceInfo_t & info)
{
	return false;
}

void CShaderDeviceVk::AllocFrameSyncObjects(void)
{
}

void CShaderDeviceVk::FreeFrameSyncObjects(void)
{
}

void CShaderDeviceVk::AllocFrameSyncTextureObject()
{
}

void CShaderDeviceVk::FreeFrameSyncTextureObject()
{
}

bool CShaderDeviceVk::AllocNonInteractiveRefreshObjects()
{
	return false;
}

void CShaderDeviceVk::FreeNonInteractiveRefreshObjects()
{
}

void CShaderDeviceVk::UpdatePresentStats()
{
}

bool CShaderDeviceVk::InNonInteractiveMode() const
{
	return false;
}

void CShaderDeviceVk::ReacquireResourcesInternal(bool bResetState, bool bForceReacquire, char const * pszForceReason)
{
}

bool CShaderDeviceVk::IsUsingGraphics() const
{
	return false;
}

ImageFormat CShaderDeviceVk::GetBackBufferFormat() const
{
	return ImageFormat();
}

void CShaderDeviceVk::GetBackBufferDimensions(int & width, int & height) const
{
}

void CShaderDeviceVk::Present()
{
}

IShaderBuffer * CShaderDeviceVk::CompileShader(const char * pProgram, size_t nBufLen, const char * pShaderVersion)
{
	return nullptr;
}

VertexShaderHandle_t CShaderDeviceVk::CreateVertexShader(IShaderBuffer * pBuffer)
{
	return VertexShaderHandle_t();
}

void CShaderDeviceVk::DestroyVertexShader(VertexShaderHandle_t hShader)
{
}

GeometryShaderHandle_t CShaderDeviceVk::CreateGeometryShader(IShaderBuffer * pShaderBuffer)
{
	return GeometryShaderHandle_t();
}

void CShaderDeviceVk::DestroyGeometryShader(GeometryShaderHandle_t hShader)
{
}

PixelShaderHandle_t CShaderDeviceVk::CreatePixelShader(IShaderBuffer * pShaderBuffer)
{
	return PixelShaderHandle_t();
}

void CShaderDeviceVk::DestroyPixelShader(PixelShaderHandle_t hShader)
{
}

void CShaderDeviceVk::ReleaseResources()
{
}

void CShaderDeviceVk::ReacquireResources()
{
}

IMesh * CShaderDeviceVk::CreateStaticMesh(VertexFormat_t format, const char * pBudgetGroup, IMaterial * pMaterial)
{
	return nullptr;
}

void CShaderDeviceVk::DestroyStaticMesh(IMesh * mesh)
{
}

IVertexBuffer * CShaderDeviceVk::CreateVertexBuffer(ShaderBufferType_t type, VertexFormat_t fmt, int nVertexCount, const char * pBudgetGroup)
{
	return nullptr;
}

void CShaderDeviceVk::DestroyVertexBuffer(IVertexBuffer * pVertexBuffer)
{
}

IIndexBuffer * CShaderDeviceVk::CreateIndexBuffer(ShaderBufferType_t bufferType, MaterialIndexFormat_t fmt, int nIndexCount, const char * pBudgetGroup)
{
	return nullptr;
}

void CShaderDeviceVk::DestroyIndexBuffer(IIndexBuffer * pIndexBuffer)
{
}

IVertexBuffer * CShaderDeviceVk::GetDynamicVertexBuffer(int nStreamID, VertexFormat_t vertexFormat, bool bBuffered)
{
	return nullptr;
}

IIndexBuffer * CShaderDeviceVk::GetDynamicIndexBuffer(MaterialIndexFormat_t fmt, bool bBuffered)
{
	return nullptr;
}

void CShaderDeviceVk::SetHardwareGammaRamp(float fGamma, float fGammaTVRangeMin, float fGammaTVRangeMax, float fGammaTVExponent, bool bTVEnabled)
{
}

void CShaderDeviceVk::SpewDriverInfo() const
{
}

int CShaderDeviceVk::GetCurrentAdapter() const
{
	return 0;
}

void CShaderDeviceVk::EnableNonInteractiveMode(MaterialNonInteractiveMode_t mode, ShaderNonInteractiveInfo_t * pInfo)
{
}

void CShaderDeviceVk::RefreshFrontBufferNonInteractive()
{
}

bool CShaderDeviceVk::InitDevice(void * hWnd, int nAdapter, const ShaderDeviceInfo_t & info)
{
	return false;
}

void CShaderDeviceVk::ShutdownDevice()
{
}

#pragma endregion