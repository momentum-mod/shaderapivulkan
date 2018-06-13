#pragma once

#include <shaderapi/ishaderapi.h>

#include "impl_vulkan.hpp"

#include "shaderapi/ishaderapi.h"
#include "shaderapi_global.h"
#include "localvktypes.h"

typedef struct _texturedat_s
{
	int placeholder;
}texturedat_t;

//-----------------------------------------------------------------------------
// The Base implementation of the shader rendering interface
//-----------------------------------------------------------------------------
class CShaderAPIBase : public IShaderAPIVK
{
public:
	// constructor, destructor
	CShaderAPIBase();
	virtual ~CShaderAPIBase();

	// Called when the device is initializing or shutting down
	virtual bool OnDeviceInit() = 0;
	virtual void OnDeviceShutdown() = 0;

	// Pix events
	virtual void BeginPIXEvent(unsigned long color, const char *szName) = 0;
	virtual void EndPIXEvent() = 0;
	virtual void AdvancePIXFrame() = 0;

	// Release, reacquire objects
	virtual void ReleaseShaderObjects() = 0;
	virtual void RestoreShaderObjects() = 0;

	// Resets the render state to its well defined initial value
	virtual void ResetRenderState(bool bFullReset = true) = 0;

	// Returns a d3d texture associated with a texture handle
	virtual texturedat_t* GetD3DTexture(ShaderAPITextureHandle_t hTexture) = 0;

	// Queues a non-full reset of render state next BeginFrame.
	virtual void QueueResetRenderState() = 0;

	// Methods of IShaderDynamicAPI
public:
	virtual void GetCurrentColorCorrection(ShaderColorCorrectionInfo_t* pInfo);

protected:
};