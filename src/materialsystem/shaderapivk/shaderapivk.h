#pragma once 

#include "shaderapi/ishaderapi.h"

class CShaderAPI : public IShaderAPI
{
public:
	CShaderAPI();
	~CShaderAPI();

	// Viewport methods
	virtual void SetViewports(int nCount, const ShaderViewport_t* pViewports) override;
	virtual int GetViewports(ShaderViewport_t* pViewports, int nMax) const override;

	// Buffer clearing
	virtual void ClearBuffers(bool bClearColor, bool bClearDepth, bool bClearStencil, int renderTargetWidth, int renderTargetHeight) override;
	virtual void ClearColor3ub(unsigned char r, unsigned char g, unsigned char b) override;
	virtual void ClearColor4ub(unsigned char r, unsigned char g, unsigned char b, unsigned char a) override;

	// Methods related to binding shaders
	virtual void BindVertexShader(VertexShaderHandle_t hVertexShader) override;
	virtual void BindGeometryShader(GeometryShaderHandle_t hGeometryShader) override;
	virtual void BindPixelShader(PixelShaderHandle_t hPixelShader) override;

	// Methods related to state objects
	virtual void SetRasterState(const ShaderRasterState_t& state) override;

	//
	// NOTE: These methods have not yet been ported to DX10
	//

	// Sets the mode...
	virtual bool SetMode(void* hwnd, int nAdapter, const ShaderDeviceInfo_t &info) override;

	virtual void ChangeVideoMode(const ShaderDeviceInfo_t &info) override;

	// Returns the snapshot id for the shader state
	virtual StateSnapshot_t	 TakeSnapshot() override;

	virtual void TexMinFilter(ShaderTexFilterMode_t texFilterMode) override;
	virtual void TexMagFilter(ShaderTexFilterMode_t texFilterMode) override;
	virtual void TexWrap(ShaderTexCoordComponent_t coord, ShaderTexWrapMode_t wrapMode) override;

	virtual void CopyRenderTargetToTexture(ShaderAPITextureHandle_t textureHandle) override;

	// Binds a particular material to render with
	virtual void Bind(IMaterial* pMaterial) override;

	// Flushes any primitives that are buffered
	virtual void FlushBufferedPrimitives() override;

	// Gets the dynamic mesh; note that you've got to render the mesh
	// before calling this function a second time. Clients should *not*
	// call DestroyStaticMesh on the mesh returned by this call.
	virtual IMesh* GetDynamicMesh(IMaterial* pMaterial, int nHWSkinBoneCount, bool bBuffered = true,
		IMesh* pVertexOverride = 0, IMesh* pIndexOverride = 0) override;
	virtual IMesh* GetDynamicMeshEx(IMaterial* pMaterial, VertexFormat_t vertexFormat, int nHWSkinBoneCount,
		bool bBuffered = true, IMesh* pVertexOverride = 0, IMesh* pIndexOverride = 0) override;

	// Methods to ask about particular state snapshots
	virtual bool IsTranslucent(StateSnapshot_t id) const override;
	virtual bool IsAlphaTested(StateSnapshot_t id) const override;
	virtual bool UsesVertexAndPixelShaders(StateSnapshot_t id) const override;
	virtual bool IsDepthWriteEnabled(StateSnapshot_t id) const override;

	// Gets the vertex format for a set of snapshot ids
	virtual VertexFormat_t ComputeVertexFormat(int numSnapshots, StateSnapshot_t* pIds) const override;

	// What fields in the vertex do we actually use?
	virtual VertexFormat_t ComputeVertexUsage(int numSnapshots, StateSnapshot_t* pIds) const override;

	// Begins a rendering pass
	virtual void BeginPass(StateSnapshot_t snapshot) override;

	// Renders a single pass of a material
	virtual void RenderPass(int nPass, int nPassCount) override;

	// Set the number of bone weights
	virtual void SetNumBoneWeights(int numBones) override;

	// Sets the lights
	virtual void SetLight(int lightNum, const LightDesc_t& desc) override;

	// Lighting origin for the current model
	virtual void SetLightingOrigin(Vector vLightingOrigin) override;

	virtual void SetAmbientLight(float r, float g, float b) override;
	virtual void SetAmbientLightCube(Vector4D cube[6]) override;

	// The shade mode
	virtual void ShadeMode(ShaderShadeMode_t mode) override;

	// The cull mode
	virtual void CullMode(MaterialCullMode_t cullMode) override;

	// Force writes only when z matches. . . useful for stenciling things out
	// by rendering the desired Z values ahead of time.
	virtual void ForceDepthFuncEquals(bool bEnable) override;

	// Forces Z buffering to be on or off
	virtual void OverrideDepthEnable(bool bEnable, bool bDepthEnable) override;

	virtual void SetHeightClipZ(float z) override;
	virtual void SetHeightClipMode(enum MaterialHeightClipMode_t heightClipMode) override;

	virtual void SetClipPlane(int index, const float *pPlane) override;
	virtual void EnableClipPlane(int index, bool bEnable) override;

	// Put all the model matrices into vertex shader constants.
	virtual void SetSkinningMatrices() override;

	// Returns the nearest supported format
	virtual ImageFormat GetNearestSupportedFormat(ImageFormat fmt, bool bFilteringRequired = true) const override;
	virtual ImageFormat GetNearestRenderTargetFormat(ImageFormat fmt) const override;

	// When AA is enabled, render targets are not AA and require a separate
	// depth buffer.
	virtual bool DoRenderTargetsNeedSeparateDepthBuffer() const override;

	// Texture management methods
	// For CreateTexture also see CreateTextures below
	virtual ShaderAPITextureHandle_t CreateTexture(
		int width,
		int height,
		int depth,
		ImageFormat dstImageFormat,
		int numMipLevels,
		int numCopies,
		int flags,
		const char *pDebugName,
		const char *pTextureGroupName) override;

	virtual void DeleteTexture(ShaderAPITextureHandle_t textureHandle) override;

	virtual ShaderAPITextureHandle_t CreateDepthTexture(
		ImageFormat renderTargetFormat,
		int width,
		int height,
		const char *pDebugName,
		bool bTexture) override;

	virtual bool IsTexture(ShaderAPITextureHandle_t textureHandle) override;
	virtual bool IsTextureResident(ShaderAPITextureHandle_t textureHandle) override;

	// Indicates we're going to be modifying this texture
	// TexImage2D, TexSubImage2D, TexWrap, TexMinFilter, and TexMagFilter
	// all use the texture specified by this function.
	virtual void ModifyTexture(ShaderAPITextureHandle_t textureHandle) override;

	virtual void TexImage2D(
		int level,
		int cubeFaceID,
		ImageFormat dstFormat,
		int zOffset,
		int width,
		int height,
		ImageFormat srcFormat,
		bool bSrcIsTiled,		// NOTE: for X360 only
		void *imageData) override;

	virtual void TexSubImage2D(
		int level,
		int cubeFaceID,
		int xOffset,
		int yOffset,
		int zOffset,
		int width,
		int height,
		ImageFormat srcFormat,
		int srcStride,
		bool bSrcIsTiled,		// NOTE: for X360 only
		void *imageData) override;

	virtual void TexImageFromVTF(IVTFTexture* pVTF, int iVTFFrame) override;

	// An alternate (and faster) way of writing image data
	// (locks the current Modify Texture). Use the pixel writer to write the data
	// after Lock is called
	// Doesn't work for compressed textures 
	virtual bool TexLock(int level, int cubeFaceID, int xOffset, int yOffset,
		int width, int height, CPixelWriter& writer) override;
	virtual void TexUnlock() override;

	// These are bound to the texture
	virtual void TexSetPriority(int priority) override;

	// Sets the texture state
	virtual void BindTexture(Sampler_t sampler, ShaderAPITextureHandle_t textureHandle) override;

	// Set the render target to a texID.
	// Set to SHADER_RENDERTARGET_BACKBUFFER if you want to use the regular framebuffer.
	// Set to SHADER_RENDERTARGET_DEPTHBUFFER if you want to use the regular z buffer.
	virtual void SetRenderTarget(ShaderAPITextureHandle_t colorTextureHandle = SHADER_RENDERTARGET_BACKBUFFER,
		ShaderAPITextureHandle_t depthTextureHandle = SHADER_RENDERTARGET_DEPTHBUFFER) override;

	// stuff that isn't to be used from within a shader
	virtual void ClearBuffersObeyStencil(bool bClearColor, bool bClearDepth) override;
	virtual void ReadPixels(int x, int y, int width, int height, unsigned char *data, ImageFormat dstFormat) override;
	virtual void ReadPixels(Rect_t *pSrcRect, Rect_t *pDstRect, unsigned char *data, ImageFormat dstFormat, int nDstStride) override;

	virtual void FlushHardware() override;

	// Use this to begin and end the frame
	virtual void BeginFrame() override;
	virtual void EndFrame() override;

	// Selection mode methods
	virtual int  SelectionMode(bool selectionMode) override;
	virtual void SelectionBuffer(unsigned int* pBuffer, int size) override;
	virtual void ClearSelectionNames() override;
	virtual void LoadSelectionName(int name) override;
	virtual void PushSelectionName(int name) override;
	virtual void PopSelectionName() override;

	// Force the hardware to finish whatever it's doing
	virtual void ForceHardwareSync() override;

	// Used to clear the transition table when we know it's become invalid.
	virtual void ClearSnapshots() override;

	virtual void FogStart(float fStart) override;
	virtual void FogEnd(float fEnd) override;
	virtual void SetFogZ(float fogZ) override;
	// Scene fog state.
	virtual void SceneFogColor3ub(unsigned char r, unsigned char g, unsigned char b) override;
	virtual void GetSceneFogColor(unsigned char *rgb) override;
	virtual void SceneFogMode(MaterialFogMode_t fogMode) override;

	// Can we download textures?
	virtual bool CanDownloadTextures() const override;

	virtual void ResetRenderState(bool bFullReset = true) override;

	// We use smaller dynamic VBs during level transitions, to free up memory
	virtual int  GetCurrentDynamicVBSize(void) override;
	virtual void DestroyVertexBuffers(bool bExitingLevel = false) override;

	virtual void EvictManagedResources() override;

	// Level of anisotropic filtering
	virtual void SetAnisotropicLevel(int nAnisotropyLevel) override;

	// For debugging and building recording files. This will stuff a token into the recording file,
	// then someone doing a playback can watch for the token.
	virtual void SyncToken(const char *pToken) override;

	// Setup standard vertex shader constants (that don't change)
	// This needs to be called anytime that overbright changes.
	virtual void SetStandardVertexShaderConstants(float fOverbright) override;

	//
	// Occlusion query support
	//

	// Allocate and delete query objects.
	virtual ShaderAPIOcclusionQuery_t CreateOcclusionQueryObject(void) override;
	virtual void DestroyOcclusionQueryObject(ShaderAPIOcclusionQuery_t) override;

	// Bracket drawing with begin and end so that we can get counts next frame.
	virtual void BeginOcclusionQueryDrawing(ShaderAPIOcclusionQuery_t) override;
	virtual void EndOcclusionQueryDrawing(ShaderAPIOcclusionQuery_t) override;

	// OcclusionQuery_GetNumPixelsRendered
	//	Get the number of pixels rendered between begin and end on an earlier frame.
	//	Calling this in the same frame is a huge perf hit!
	// Returns iQueryResult:
	//	iQueryResult >= 0					-	iQueryResult is the number of pixels rendered
	//	OCCLUSION_QUERY_RESULT_PENDING		-	query results are not available yet
	//	OCCLUSION_QUERY_RESULT_ERROR		-	query failed
	// Use OCCLUSION_QUERY_FINISHED( iQueryResult ) to test if query finished.
	virtual int OcclusionQuery_GetNumPixelsRendered(ShaderAPIOcclusionQuery_t hQuery, bool bFlush = false) override;

	virtual void SetFlashlightState(const FlashlightState_t &state, const VMatrix &worldToTexture) override;

	virtual void ClearVertexAndPixelShaderRefCounts() override;
	virtual void PurgeUnusedVertexAndPixelShaders() override;

	// Called when the dx support level has changed
	virtual void DXSupportLevelChanged() override;

	// By default, the material system applies the VIEW and PROJECTION matrices	to the user clip
	// planes (which are specified in world space) to generate projection-space user clip planes
	// Occasionally (for the particle system in hl2, for example), we want to override that
	// behavior and explictly specify a View transform for user clip planes. The PROJECTION
	// will be mutliplied against this instead of the normal VIEW matrix.
	virtual void EnableUserClipTransformOverride(bool bEnable) override;
	virtual void UserClipTransform(const VMatrix &worldToView) override;

	// ----------------------------------------------------------------------------------
	// Everything after this point added after HL2 shipped.
	// ----------------------------------------------------------------------------------

	// What fields in the morph do we actually use?
	virtual MorphFormat_t ComputeMorphFormat(int numSnapshots, StateSnapshot_t* pIds) const override;

	// Set the render target to a texID.
	// Set to SHADER_RENDERTARGET_BACKBUFFER if you want to use the regular framebuffer.
	// Set to SHADER_RENDERTARGET_DEPTHBUFFER if you want to use the regular z buffer.
	virtual void SetRenderTargetEx(int nRenderTargetID,
		ShaderAPITextureHandle_t colorTextureHandle = SHADER_RENDERTARGET_BACKBUFFER,
		ShaderAPITextureHandle_t depthTextureHandle = SHADER_RENDERTARGET_DEPTHBUFFER) override;

	virtual void CopyRenderTargetToTextureEx(ShaderAPITextureHandle_t textureHandle, int nRenderTargetID, Rect_t *pSrcRect = NULL, Rect_t *pDstRect = NULL) override;
	virtual void CopyTextureToRenderTargetEx(int nRenderTargetID, ShaderAPITextureHandle_t textureHandle, Rect_t *pSrcRect = NULL, Rect_t *pDstRect = NULL) override;

	// For dealing with device lost in cases where SwapBuffers isn't called all the time (Hammer)
	virtual void HandleDeviceLost() override;

	virtual void EnableLinearColorSpaceFrameBuffer(bool bEnable) override;

	// Lets the shader know about the full-screen texture so it can 
	virtual void SetFullScreenTextureHandle(ShaderAPITextureHandle_t h) override;

	// Rendering parameters control special drawing modes withing the material system, shader
	// system, shaders, and engine. renderparm.h has their definitions.
	virtual void SetFloatRenderingParameter(int parm_number, float value) override;
	virtual void SetIntRenderingParameter(int parm_number, int value) override;
	virtual void SetVectorRenderingParameter(int parm_number, Vector const &value) override;

	virtual float GetFloatRenderingParameter(int parm_number) const override;
	virtual int GetIntRenderingParameter(int parm_number) const override;
	virtual Vector GetVectorRenderingParameter(int parm_number) const override;

	virtual void SetFastClipPlane(const float *pPlane) override;
	virtual void EnableFastClip(bool bEnable) override;

	// Returns the number of vertices + indices we can render using the dynamic mesh
	// Passing true in the second parameter will return the max # of vertices + indices
	// we can use before a flush is provoked and may return different values 
	// if called multiple times in succession. 
	// Passing false into the second parameter will return
	// the maximum possible vertices + indices that can be rendered in a single batch
	virtual void GetMaxToRender(IMesh *pMesh, bool bMaxUntilFlush, int *pMaxVerts, int *pMaxIndices) override;

	// Returns the max number of vertices we can render for a given material
	virtual int GetMaxVerticesToRender(IMaterial *pMaterial) override;
	virtual int GetMaxIndicesToRender() override;

	// stencil methods
	virtual void SetStencilEnable(bool onoff) override;
	virtual void SetStencilFailOperation(StencilOperation_t op) override;
	virtual void SetStencilZFailOperation(StencilOperation_t op) override;
	virtual void SetStencilPassOperation(StencilOperation_t op) override;
	virtual void SetStencilCompareFunction(StencilComparisonFunction_t cmpfn) override;
	virtual void SetStencilReferenceValue(int ref) override;
	virtual void SetStencilTestMask(uint32 msk) override;
	virtual void SetStencilWriteMask(uint32 msk) override;
	virtual void ClearStencilBufferRectangle(int xmin, int ymin, int xmax, int ymax, int value) override;

	// disables all local lights
	virtual void DisableAllLocalLights() override;
	virtual int CompareSnapshots(StateSnapshot_t snapshot0, StateSnapshot_t snapshot1) override;

	virtual IMesh *GetFlexMesh() override;

	virtual void SetFlashlightStateEx(const FlashlightState_t &state, const VMatrix &worldToTexture, ITexture *pFlashlightDepthTexture) override;

	virtual bool SupportsMSAAMode(int nMSAAMode) override;

	virtual bool OwnGPUResources(bool bEnable) override;

	//get fog distances entered with FogStart(), FogEnd(), and SetFogZ()
	virtual void GetFogDistances(float *fStart, float *fEnd, float *fFogZ) override;

	// Hooks for firing PIX events from outside the Material System...
	virtual void BeginPIXEvent(unsigned long color, const char *szName) override;
	virtual void EndPIXEvent() override;
	virtual void SetPIXMarker(unsigned long color, const char *szName) override;

	// Enables and disables for Alpha To Coverage
	virtual void EnableAlphaToCoverage() override;
	virtual void DisableAlphaToCoverage() override;

	// Computes the vertex buffer pointers 
	virtual void ComputeVertexDescription(unsigned char* pBuffer, VertexFormat_t vertexFormat, MeshDesc_t& desc) const override;

	virtual bool SupportsShadowDepthTextures(void) override;

	virtual void SetDisallowAccess(bool) override;
	virtual void EnableShaderShaderMutex(bool) override;
	virtual void ShaderLock() override;
	virtual void ShaderUnlock() override;

	virtual ImageFormat GetShadowDepthTextureFormat(void) override;

	virtual bool SupportsFetch4(void) override;
	virtual void SetShadowDepthBiasFactors(float fShadowSlopeScaleDepthBias, float fShadowDepthBias) override;

	// ------------ New Vertex/Index Buffer interface ----------------------------
	virtual void BindVertexBuffer(int nStreamID, IVertexBuffer *pVertexBuffer, int nOffsetInBytes, int nFirstVertex, int nVertexCount, VertexFormat_t fmt, int nRepetitions = 1) override;
	virtual void BindIndexBuffer(IIndexBuffer *pIndexBuffer, int nOffsetInBytes) override;
	virtual void Draw(MaterialPrimitiveType_t primitiveType, int nFirstIndex, int nIndexCount) override;
	// ------------ End ----------------------------


	// Apply stencil operations to every pixel on the screen without disturbing depth or color buffers
	virtual void PerformFullScreenStencilOperation(void) override;

	virtual void SetScissorRect(const int nLeft, const int nTop, const int nRight, const int nBottom, const bool bEnableScissor) override;

	// nVidia CSAA modes, different from SupportsMSAAMode()
	virtual bool SupportsCSAAMode(int nNumSamples, int nQualityLevel) override;

	//Notifies the shaderapi to invalidate the current set of delayed constants because we just finished a draw pass. Either actual or not.
	virtual void InvalidateDelayedShaderConstants(void) override;

	// Gamma<->Linear conversions according to the video hardware we're running on
	virtual float GammaToLinear_HardwareSpecific(float fGamma) const override;
	virtual float LinearToGamma_HardwareSpecific(float fLinear) const override;

	//Set's the linear->gamma conversion textures to use for this hardware for both srgb writes enabled and disabled(identity)
	virtual void SetLinearToGammaConversionTextures(ShaderAPITextureHandle_t hSRGBWriteEnabledTexture, ShaderAPITextureHandle_t hIdentityTexture) override;

	virtual ImageFormat GetNullTextureFormat(void) override;

	virtual void BindVertexTexture(VertexTextureSampler_t nSampler, ShaderAPITextureHandle_t textureHandle) override;

	// Enables hardware morphing
	virtual void EnableHWMorphing(bool bEnable) override;

	// Sets flexweights for rendering
	virtual void SetFlexWeights(int nFirstWeight, int nCount, const MorphWeight_t* pWeights) override;

	virtual void FogMaxDensity(float flMaxDensity) override;

	// Create a multi-frame texture (equivalent to calling "CreateTexture" multiple times, but more efficient)
	virtual void CreateTextures(
		ShaderAPITextureHandle_t *pHandles,
		int count,
		int width,
		int height,
		int depth,
		ImageFormat dstImageFormat,
		int numMipLevels,
		int numCopies,
		int flags,
		const char *pDebugName,
		const char *pTextureGroupName) override;

	virtual void AcquireThreadOwnership() override;
	virtual void ReleaseThreadOwnership() override;

	virtual bool SupportsNormalMapCompression() const override;

	// Only does anything on XBox360. This is useful to eliminate stalls
	virtual void EnableBuffer2FramesAhead(bool bEnable) override;

	virtual void SetDepthFeatheringPixelShaderConstant(int iConstant, float fDepthBlendScale) override;

	// debug logging
	// only implemented in some subclasses
	virtual void PrintfVA(char *fmt, va_list vargs) override;
	virtual void Printf(PRINTF_FORMAT_STRING const char *fmt, ...) override;
	virtual float Knob(char *knobname, float *setvalue = NULL) override;
	// Allows us to override the alpha write setting of a material
	virtual void OverrideAlphaWriteEnable(bool bEnable, bool bAlphaWriteEnable) override;
	virtual void OverrideColorWriteEnable(bool bOverrideEnable, bool bColorWriteEnable) override;

	//extended clear buffers function with alpha independent from color
	virtual void ClearBuffersObeyStencilEx(bool bClearColor, bool bClearAlpha, bool bClearDepth) override;

	// Allows copying a render target to another texture by specifying them both.
	virtual void CopyRenderTargetToScratchTexture(ShaderAPITextureHandle_t srcRt, ShaderAPITextureHandle_t dstTex, Rect_t *pSrcRect = NULL, Rect_t *pDstRect = NULL) override;

	// Allows locking and unlocking of very specific surface types.
	virtual void LockRect(void** pOutBits, int* pOutPitch, ShaderAPITextureHandle_t texHandle, int mipmap, int x, int y, int w, int h, bool bWrite, bool bRead) override;
	virtual void UnlockRect(ShaderAPITextureHandle_t texHandle, int mipmap) override;
};

extern CShaderAPI* g_pShaderAPI;