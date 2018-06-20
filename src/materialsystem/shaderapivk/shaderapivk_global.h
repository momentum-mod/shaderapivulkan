#pragma once

#include "tier2/tier2.h"
#include "shaderapivk.h"

/*#include "d3d_async.h"
typedef D3DDeviceWrapper D3DDev_t;
D3DDev_t *Dx9Device();
IDirect3D9 *D3D();*/


//-----------------------------------------------------------------------------
// Measures driver allocations
//-----------------------------------------------------------------------------
//#define MEASURE_DRIVER_ALLOCATIONS 1


//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------
class IShaderUtil;
class IVertexBufferDX8;
class IShaderShadowDX8;
class IMeshMgr;
class IShaderAPIDX8;
class IFileSystem;
class IShaderManager;


//-----------------------------------------------------------------------------
// A new shader draw flag we need to workaround dx8
//-----------------------------------------------------------------------------
enum
{
    SHADER_HAS_CONSTANT_COLOR = 0x80000000
};

//-----------------------------------------------------------------------------
// The main shader API
//-----------------------------------------------------------------------------
inline IShaderAPI* ShaderAPI()
{
    return g_pShaderAPI;
}

//-----------------------------------------------------------------------------
// The shader shadow
//-----------------------------------------------------------------------------
IShaderShadowDX8* ShaderShadow();

//-----------------------------------------------------------------------------
// Manager of all vertex + pixel shaders
//-----------------------------------------------------------------------------
inline IShaderManager *ShaderManager()
{
    extern IShaderManager *g_pShaderManager;
    return g_pShaderManager;
}

//-----------------------------------------------------------------------------
// The mesh manager
//-----------------------------------------------------------------------------
IMeshMgr* MeshMgr();

//-----------------------------------------------------------------------------
// The main hardware config interface
//-----------------------------------------------------------------------------
inline IMaterialSystemHardwareConfig* HardwareConfig()
{
    return g_pMaterialSystemHardwareConfig;
}
