#pragma once

//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------
class IShaderUtil;
class CShaderDevice;
class CShaderDeviceMgr;
class CShaderAPI;
class IShaderShadow;


//-----------------------------------------------------------------------------
// Global interfaces
//-----------------------------------------------------------------------------
extern IShaderUtil* g_pShaderUtil;
inline IShaderUtil* ShaderUtil()
{
    return g_pShaderUtil;
}

extern CShaderDevice *g_pShaderDevice;
extern CShaderDeviceMgr *g_pShaderDeviceMgr;
extern CShaderAPI *g_pShaderAPI;
extern IShaderShadow *g_pShaderShadow;