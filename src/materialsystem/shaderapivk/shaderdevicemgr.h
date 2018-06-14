#pragma once

#include "shaderapi/IShaderDevice.h"

#include "vulkanimpl.h"

struct MyVkAdapterInfo
{

};

class CShaderDeviceMgr : public IShaderDeviceMgr
{
public:
#pragma region IAppSystem
	// Here's where the app systems get to learn about each other 
	virtual bool Connect(CreateInterfaceFn factory) override;
	virtual void Disconnect() override;

	// Here's where systems can access other interfaces implemented by this object
	// Returns NULL if it doesn't implement the requested interface
	virtual void *QueryInterface(const char *pInterfaceName) override;

	// Init, shutdown
	virtual InitReturnVal_t Init() override;
	virtual void Shutdown() override;
#pragma endregion

#pragma region IShaderDeviceMgr
	// Gets the number of adapters...
	virtual int	 GetAdapterCount() const override;

	// Returns info about each adapter
	virtual void GetAdapterInfo(int nAdapter, MaterialAdapterInfo_t& info) const override;

	// Gets recommended congifuration for a particular adapter at a particular dx level
	virtual bool GetRecommendedConfigurationInfo(int nAdapter, int nDXLevel, KeyValues *pConfiguration) override;

	// Returns the number of modes
	virtual int	 GetModeCount(int nAdapter) const override;

	// Returns mode information..
	virtual void GetModeInfo(ShaderDisplayMode_t* pInfo, int nAdapter, int nMode) const override;

	// Returns the current mode info for the requested adapter
	virtual void GetCurrentModeInfo(ShaderDisplayMode_t* pInfo, int nAdapter) const override;

	// Initialization, shutdown
	virtual bool SetAdapter(int nAdapter, int nFlags) override;

	// Sets the mode
	// Use the returned factory to get at an IShaderDevice and an IShaderRender
	// and any other interfaces we decide to create.
	// A returned factory of NULL indicates the mode was not set properly.
	virtual CreateInterfaceFn SetMode(void *hWnd, int nAdapter, const ShaderDeviceInfo_t& mode) override;

	// Installs a callback to get called 
	virtual void AddModeChangeCallback(ShaderModeChangeCallbackFunc_t func) override;
	virtual void RemoveModeChangeCallback(ShaderModeChangeCallbackFunc_t func) override;
#pragma endregion

	VkInstance GetInstance();

private:
	VkInstance m_hInstance;
	CUtlVector<MyVkAdapterInfo> m_Adapters;
};

extern CShaderDeviceMgr* g_pShaderDeviceMgr;