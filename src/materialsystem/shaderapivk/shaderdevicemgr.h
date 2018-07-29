#pragma once

#include "shaderapi/IShaderDevice.h"
#include "shaderapi/ishaderapi.h"

#include "vulkanimpl.h"

enum CompressedTextureState_t
{
	COMPRESSED_TEXTURES_ON,
	COMPRESSED_TEXTURES_OFF,
	COMPRESSED_TEXTURES_NOT_INITIALIZED
};

struct MyHardwareCaps
{

	CompressedTextureState_t m_SupportsCompressedTextures;
	VertexCompressionType_t m_SupportsCompressedVertices;
	int  m_NumSamplers;
	int  m_NumTextureStages;
	int	 m_nMaxAnisotropy;
	int  m_MaxTextureWidth;
	int  m_MaxTextureHeight;
	int  m_MaxTextureDepth;
	int	 m_MaxTextureAspectRatio;
	int  m_MaxPrimitiveCount;
	int  m_NumPixelShaderConstants;
	int  m_NumBooleanPixelShaderConstants;
	int  m_NumIntegerPixelShaderConstants;
	int  m_NumVertexShaderConstants;
	int  m_NumBooleanVertexShaderConstants;
	int  m_NumIntegerVertexShaderConstants;
	int  m_TextureMemorySize;
	int  m_MaxNumLights;
	int  m_MaxBlendMatrices;
	int  m_MaxBlendMatrixIndices;
	int	 m_MaxVertexShaderBlendMatrices;
	int  m_MaxUserClipPlanes;
	HDRType_t m_HDRType;
	char m_pShaderDLL[32];
	ImageFormat m_ShadowDepthTextureFormat;
	ImageFormat m_NullTextureFormat;
	int  m_nVertexTextureCount;
	int  m_nMaxVertexTextureDimension;
	unsigned long m_AlphaToCoverageState;					// State to ping to toggle Alpha To Coverage              (vendor-dependent)
	unsigned long m_AlphaToCoverageEnableValue;				// Value to set above state to turn on Alpha To Coverage  (vendor-dependent)
	unsigned long m_AlphaToCoverageDisableValue;			// Value to set above state to turn off Alpha To Coverage (vendor-dependent)
	int	 m_nMaxViewports;
	float m_flMinGammaControlPoint;
	float m_flMaxGammaControlPoint;
	int m_nGammaControlPointCount;
	int m_MaxVertexShader30InstructionSlots;
	int m_MaxPixelShader30InstructionSlots;
	int m_MaxSimultaneousRenderTargets;

	bool m_bDeviceOk : 1;
	bool m_HasSetDeviceGammaRamp : 1;
	bool m_SupportsVertexShaders : 1;
	bool m_SupportsVertexShaders_2_0 : 1;
	bool m_SupportsPixelShaders : 1;
	bool m_SupportsPixelShaders_1_4 : 1;
	bool m_SupportsPixelShaders_2_0 : 1;
	bool m_SupportsPixelShaders_2_b : 1;
	bool m_SupportsShaderModel_3_0 : 1;
	bool m_bSupportsAnisotropicFiltering : 1;
	bool m_bSupportsMagAnisotropicFiltering : 1;
	bool m_bSupportsVertexTextures : 1;
	bool m_ZBiasAndSlopeScaledDepthBiasSupported : 1;
	bool m_SupportsMipmapping : 1;
	bool m_SupportsOverbright : 1;
	bool m_SupportsCubeMaps : 1;
	bool m_SupportsHardwareLighting : 1;
	bool m_SupportsMipmappedCubemaps : 1;
	bool m_SupportsNonPow2Textures : 1;
	bool m_PreferDynamicTextures : 1;
	bool m_HasProjectedBumpEnv : 1;
	bool m_SupportsSRGB : 1;
	bool m_bSupportsSpheremapping : 1;
	bool m_UseFastClipping : 1;
	bool m_bNeedsATICentroidHack : 1;
	bool m_bDisableShaderOptimizations : 1;
	bool m_bColorOnSecondStream : 1;
	bool m_bSupportsStreamOffset : 1;
	bool m_bFogColorSpecifiedInLinearSpace : 1;
	bool m_bFogColorAlwaysLinearSpace : 1;
	bool m_bSupportsAlphaToCoverage : 1;
	bool m_bSupportsShadowDepthTextures : 1;
	bool m_bSupportsFetch4 : 1;
	bool m_bSoftwareVertexProcessing : 1;
	bool m_bScissorSupported : 1;
	bool m_bSupportsFloat32RenderTargets : 1;
	bool m_bSupportsNormalMapCompression : 1;
	bool m_bSupportsBorderColor : 1;

	HDRType_t m_MaxHDRType;
};

struct MyVkAdapterInfo
{
	MaterialAdapterInfo_t matdata;
	VkPhysicalDeviceProperties props;
	MyHardwareCaps caps;
	VkPhysicalDevice device;
	ShaderDisplayMode_t shaderMode;
};

class CShaderDeviceMgr : public IShaderDeviceMgr
{
public:
    CShaderDeviceMgr();
    ~CShaderDeviceMgr();

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

    void CreateVkInstance();
    void CreateVkSurface();

    void CleanupVulkan();
    void DestroyVkSurface();

	VkPhysicalDevice GetAdapter(int nIndex) const;

	void InitAdapterInfo();

	VkInstance GetInstance();

private:
	static void* MyCreateInterface(const char* pInterfaceName, int* pReturnCode);

    void *m_hWnd;

	int m_nCurAdapter;

	ShaderDeviceInfo_t m_Mode;
	VkInstance m_hInstance;
    VkSurfaceKHR m_hSurface;
	CUtlVector<MyVkAdapterInfo> m_Adapters;
};

extern CShaderDeviceMgr* g_pShaderDeviceMgr;

inline VkInstance vkinstance()
{
	return g_pShaderDeviceMgr->GetInstance();
}