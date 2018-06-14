#include "shaderapivk.h"
#include "shaderdevice.h"
#include "shaderdevicemgr.h"
#include "shaderutil.h"

CShaderDevice* g_pShaderDevice;
CShaderDeviceMgr* g_pShaderDeviceMgr;

EXPOSE_INTERFACE(CShaderDevice, IShaderDevice, SHADER_DEVICE_INTERFACE_VERSION);
EXPOSE_INTERFACE(CShaderDeviceMgr, IShaderDeviceMgr, SHADER_DEVICE_MGR_INTERFACE_VERSION);
EXPOSE_INTERFACE(CShaderUtil, IShaderUtil, SHADER_UTIL_INTERFACE_VERSION);