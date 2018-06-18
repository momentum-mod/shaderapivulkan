#include "shaderdevice.h"

CShaderDevice::CShaderDevice(DeviceCreationInfo_t& info)
{
}

CShaderDevice::~CShaderDevice()
{
}

void CShaderDevice::ReleaseResources()
{
}

void CShaderDevice::ReacquireResources()
{
}

ImageFormat CShaderDevice::GetBackBufferFormat() const
{
	return ImageFormat();
}

void CShaderDevice::GetBackBufferDimensions(int & width, int & height) const
{
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
	return nullptr;
}

void CShaderDevice::ShutdownDevice()
{
}
