#pragma once

#include "shaderapi/ishaderutil.h"

class CShaderUtil : public IShaderUtil
{
public:
	CShaderUtil();
	~CShaderUtil();

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

#pragma region IShaderUtil
	// Method to allow clients access to the MaterialSystem_Config
	virtual MaterialSystem_Config_t& GetConfig() override;

	// Allows us to convert image formats
	virtual bool ConvertImageFormat(unsigned char *src, enum ImageFormat srcImageFormat,
		unsigned char *dst, enum ImageFormat dstImageFormat,
		int width, int height, int srcStride = 0, int dstStride = 0) override;

	// Figures out the amount of memory needed by a bitmap
	virtual int GetMemRequired(int width, int height, int depth, ImageFormat format, bool mipmap) override;

	// Gets image format info
	virtual const ImageFormatInfo_t& ImageFormatInfo(ImageFormat fmt) const override;

	// Bind standard textures
	virtual void BindStandardTexture(Sampler_t sampler, StandardTextureId_t id) override;

	// What are the lightmap dimensions?
	virtual void GetLightmapDimensions(int *w, int *h) override;

	// These methods are called when the shader must eject + restore HW memory
	virtual void ReleaseShaderObjects() override;
	virtual void RestoreShaderObjects(CreateInterfaceFn shaderFactory, int nChangeFlags = 0) override;

	// Used to prevent meshes from drawing.
	virtual bool IsInStubMode() override;
	virtual bool InFlashlightMode() const override;

	// For the shader API to shove the current version of aniso level into the
	// "definitive" place (g_config) when the shader API decides to change it.
	// Eventually, we should have a better system of who owns the definitive
	// versions of config vars.
	virtual void NoteAnisotropicLevel(int currentLevel) override;

	// NOTE: Stuff after this is added after shipping HL2.

	// Are we rendering through the editor?
	virtual bool InEditorMode() const override;

	// Gets the bound morph's vertex format; returns 0 if no morph is bound
	virtual MorphFormat_t GetBoundMorphFormat() override;

	virtual ITexture *GetRenderTargetEx(int nRenderTargetID) override;

	// Tells the material system to draw a buffer clearing quad
	virtual void DrawClearBufferQuad(unsigned char r, unsigned char g, unsigned char b, unsigned char a, bool bClearColor, bool bClearAlpha, bool bClearDepth) override;

	// Calls from meshes to material system to handle queing/threading
	virtual bool OnDrawMesh(IMesh *pMesh, int firstIndex, int numIndices) override;
	virtual bool OnDrawMesh(IMesh *pMesh, CPrimList *pLists, int nLists) override;
	virtual bool OnSetFlexMesh(IMesh *pStaticMesh, IMesh *pMesh, int nVertexOffsetInBytes) override;
	virtual bool OnSetColorMesh(IMesh *pStaticMesh, IMesh *pMesh, int nVertexOffsetInBytes) override;
	virtual bool OnSetPrimitiveType(IMesh *pMesh, MaterialPrimitiveType_t type) override;
	virtual bool OnFlushBufferedPrimitives() override;


	virtual void SyncMatrices() override;
	virtual void SyncMatrix(MaterialMatrixMode_t) override;

	virtual void BindStandardVertexTexture(VertexTextureSampler_t sampler, StandardTextureId_t id) override;
	virtual void GetStandardTextureDimensions(int *pWidth, int *pHeight, StandardTextureId_t id) override;

	virtual int MaxHWMorphBatchCount() const override;

	// Interface for mat system to tell shaderapi about color correction
	virtual void GetCurrentColorCorrection(ShaderColorCorrectionInfo_t* pInfo) override;
	// received an event while not in owning thread, handle this outside
	virtual void OnThreadEvent(uint32 threadEvent) override;

	virtual MaterialThreadMode_t	GetThreadMode() override;
	virtual bool					IsRenderThreadSafe() override;

	// Remove any materials from memory that aren't in use as determined
	// by the IMaterial's reference count.
	virtual void UncacheUnusedMaterials(bool bRecomputeStateSnapshots = false) override;
#pragma endregion
};

extern CShaderUtil* g_pShaderUtil;