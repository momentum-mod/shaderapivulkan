#include "shaderdevicebase.h"

#pragma region Shader Device Manager Base
CShaderDeviceMgrBase::CShaderDeviceMgrBase()
{
}

CShaderDeviceMgrBase::~CShaderDeviceMgrBase()
{
}

bool CShaderDeviceMgrBase::Connect(CreateInterfaceFn factory)
{
	return false;
}

void CShaderDeviceMgrBase::Disconnect()
{
}

void * CShaderDeviceMgrBase::QueryInterface(const char * pInterfaceName)
{
	return nullptr;
}

bool CShaderDeviceMgrBase::GetRecommendedConfigurationInfo(int nAdapter, int nDXLevel, KeyValues * pCongifuration)
{
	return false;
}

void CShaderDeviceMgrBase::AddModeChangeCallback(ShaderModeChangeCallbackFunc_t func)
{
}

void CShaderDeviceMgrBase::RemoveModeChangeCallback(ShaderModeChangeCallbackFunc_t func)
{
}

void CShaderDeviceMgrBase::ReadHardwareCaps(HardwareCaps_t & caps, int nDxLevel)
{
}

void CShaderDeviceMgrBase::ReadDXSupportLevels(HardwareCaps_t & caps)
{
}

const HardwareCaps_t & CShaderDeviceMgrBase::GetHardwareCaps(int nAdapter) const
{
	// TODO: hier Rückgabeanweisung eingeben
}

void CShaderDeviceMgrBase::InvokeModeChangeCallbacks()
{
}

void * CShaderDeviceMgrBase::ShaderInterfaceFactory(const char * pInterfaceName, int * pReturnCode)
{
	return nullptr;
}

int CShaderDeviceMgrBase::GetClosestActualDXLevel(int nDxLevel) const
{
	return 0;
}

int CShaderDeviceMgrBase::GetVidMemBytes(int nAdapter) const
{
	return 0;
}

#pragma endregion

ImageFormat CShaderDeviceBase::GetBackBufferFormat() const
{
	return ImageFormat();
}
