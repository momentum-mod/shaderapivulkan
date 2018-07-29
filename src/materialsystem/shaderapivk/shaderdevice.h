#pragma once

#include "shaderapi/IShaderDevice.h"

#include "vulkanimpl.h"

struct MyVkAdapterInfo;

class CShaderDevice : public IShaderDevice
{
	ImageFormat _backBufferFormat;
	int _backBufferSize[2];
public:
    CShaderDevice();
	~CShaderDevice();

    void InitDevice(VkSurfaceKHR surface, MyVkAdapterInfo &adapterInfo, const ShaderDeviceInfo_t &creationInfo);

	// Releases/reloads resources when other apps want some memory
	virtual void ReleaseResources() override;
	virtual void ReacquireResources() override;

	// returns the backbuffer format and dimensions
	virtual ImageFormat GetBackBufferFormat() const override;
	virtual void GetBackBufferDimensions(int& width, int& height) const override;

	// Returns the current adapter in use
	virtual int GetCurrentAdapter() const override;

	// Are we using graphics?
	virtual bool IsUsingGraphics() const override;

	// Use this to spew information about the 3D layer 
	virtual void SpewDriverInfo() const override;

	// What's the bit depth of the stencil buffer?
	virtual int StencilBufferBits() const override;

	// Are we using a mode that uses MSAA
	virtual bool IsAAEnabled() const override;

	// Does a page flip
	virtual void Present() override;

	// Returns the window size
	virtual void GetWindowSize(int &nWidth, int &nHeight) const override;

	// Gamma ramp control
	virtual void SetHardwareGammaRamp(float fGamma, float fGammaTVRangeMin, float fGammaTVRangeMax, float fGammaTVExponent, bool bTVEnabled) override;

	// Creates/ destroys a child window
	virtual bool AddView(void* hWnd) override;
	virtual void RemoveView(void* hWnd) override;

	// Activates a view
	virtual void SetView(void* hWnd) override;

	// Shader compilation
	virtual IShaderBuffer* CompileShader(const char *pProgram, size_t nBufLen, const char *pShaderVersion) override;

	// Shader creation, destruction
	virtual VertexShaderHandle_t CreateVertexShader(IShaderBuffer* pShaderBuffer) override;
	virtual void DestroyVertexShader(VertexShaderHandle_t hShader) override;
	virtual GeometryShaderHandle_t CreateGeometryShader(IShaderBuffer* pShaderBuffer) override;
	virtual void DestroyGeometryShader(GeometryShaderHandle_t hShader) override;
	virtual PixelShaderHandle_t CreatePixelShader(IShaderBuffer* pShaderBuffer) override;
	virtual void DestroyPixelShader(PixelShaderHandle_t hShader) override;

	// Utility methods to make shader creation simpler
	// NOTE: For the utlbuffer version, use a binary buffer for a compiled shader
	// and a text buffer for a source-code (.fxc) shader
	VertexShaderHandle_t CreateVertexShader(const char *pProgram, size_t nBufLen, const char *pShaderVersion);
	VertexShaderHandle_t CreateVertexShader(CUtlBuffer &buf, const char *pShaderVersion = NULL);
	GeometryShaderHandle_t CreateGeometryShader(const char *pProgram, size_t nBufLen, const char *pShaderVersion);
	GeometryShaderHandle_t CreateGeometryShader(CUtlBuffer &buf, const char *pShaderVersion = NULL);
	PixelShaderHandle_t CreatePixelShader(const char *pProgram, size_t nBufLen, const char *pShaderVersion);
	PixelShaderHandle_t CreatePixelShader(CUtlBuffer &buf, const char *pShaderVersion = NULL);

	// NOTE: Deprecated!! Use CreateVertexBuffer/CreateIndexBuffer instead
	// Creates/destroys Mesh
	virtual IMesh* CreateStaticMesh(VertexFormat_t vertexFormat, const char *pTextureBudgetGroup, IMaterial * pMaterial = NULL) override {}
	virtual void DestroyStaticMesh(IMesh* mesh) override {}

	// Creates/destroys static vertex + index buffers
	virtual IVertexBuffer *CreateVertexBuffer(ShaderBufferType_t type, VertexFormat_t fmt, int nVertexCount, const char *pBudgetGroup) override;
	virtual void DestroyVertexBuffer(IVertexBuffer *pVertexBuffer) override;

	virtual IIndexBuffer *CreateIndexBuffer(ShaderBufferType_t bufferType, MaterialIndexFormat_t fmt, int nIndexCount, const char *pBudgetGroup) override;
	virtual void DestroyIndexBuffer(IIndexBuffer *pIndexBuffer) override;

	// Do we need to specify the stream here in the case of locking multiple dynamic VBs on different streams?
	virtual IVertexBuffer *GetDynamicVertexBuffer(int nStreamID, VertexFormat_t vertexFormat, bool bBuffered = true) override;
	virtual IIndexBuffer *GetDynamicIndexBuffer(MaterialIndexFormat_t fmt, bool bBuffered = true) override;

	// A special path used to tick the front buffer while loading on the 360
	virtual void EnableNonInteractiveMode(MaterialNonInteractiveMode_t mode, ShaderNonInteractiveInfo_t *pInfo = NULL) override;
	virtual void RefreshFrontBufferNonInteractive() override;
	virtual void HandleThreadEvent(uint32 threadEvent) override;

	virtual char *GetDisplayDeviceName() override;

	void ShutdownDevice();

	VkDevice GetDevice();

private:
	VkDevice m_Device;
	VkQueue m_Queue;
};

extern CShaderDevice* g_pShaderDevice;