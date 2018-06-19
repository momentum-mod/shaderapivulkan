#include "shaderapivk.h"

CShaderAPI::CShaderAPI()
{
}

CShaderAPI::~CShaderAPI()
{
}

void CShaderAPI::GetMaxToRender(IMesh * pMesh, bool bMaxUntilFlush, int * pMaxVerts, int * pMaxIndices)
{
}

int CShaderAPI::GetMaxVerticesToRender(IMaterial * pMaterial)
{
	return 0;
}

int CShaderAPI::GetMaxIndicesToRender()
{
	return 0;
}

void CShaderAPI::SetStencilEnable(bool onoff)
{
}

void CShaderAPI::SetStencilFailOperation(StencilOperation_t op)
{
}

void CShaderAPI::SetStencilZFailOperation(StencilOperation_t op)
{
}

void CShaderAPI::SetStencilPassOperation(StencilOperation_t op)
{
}

void CShaderAPI::SetStencilCompareFunction(StencilComparisonFunction_t cmpfn)
{
}

void CShaderAPI::SetStencilReferenceValue(int ref)
{
}

void CShaderAPI::SetStencilTestMask(uint32 msk)
{
}

void CShaderAPI::SetStencilWriteMask(uint32 msk)
{
}

void CShaderAPI::ClearStencilBufferRectangle(int xmin, int ymin, int xmax, int ymax, int value)
{
}

void CShaderAPI::DisableAllLocalLights()
{
}

int CShaderAPI::CompareSnapshots(StateSnapshot_t snapshot0, StateSnapshot_t snapshot1)
{
	return 0;
}

IMesh * CShaderAPI::GetFlexMesh()
{
	return nullptr;
}

void CShaderAPI::SetFlashlightStateEx(const FlashlightState_t & state, const VMatrix & worldToTexture, ITexture * pFlashlightDepthTexture)
{
}

bool CShaderAPI::SupportsMSAAMode(int nMSAAMode)
{
	return false;
}

bool CShaderAPI::OwnGPUResources(bool bEnable)
{
	return false;
}

void CShaderAPI::GetFogDistances(float * fStart, float * fEnd, float * fFogZ)
{
}

void CShaderAPI::BeginPIXEvent(unsigned long color, const char * szName)
{
}

void CShaderAPI::EndPIXEvent()
{
}

void CShaderAPI::SetPIXMarker(unsigned long color, const char * szName)
{
}

void CShaderAPI::EnableAlphaToCoverage()
{
}

void CShaderAPI::DisableAlphaToCoverage()
{
}

void CShaderAPI::ComputeVertexDescription(unsigned char * pBuffer, VertexFormat_t vertexFormat, MeshDesc_t & desc) const
{
}

bool CShaderAPI::SupportsShadowDepthTextures(void)
{
	return false;
}

void CShaderAPI::SetDisallowAccess(bool)
{
}

void CShaderAPI::EnableShaderShaderMutex(bool)
{
}

void CShaderAPI::ShaderLock()
{
}

void CShaderAPI::ShaderUnlock()
{
}

ImageFormat CShaderAPI::GetShadowDepthTextureFormat(void)
{
	return ImageFormat();
}

bool CShaderAPI::SupportsFetch4(void)
{
	return false;
}

void CShaderAPI::SetShadowDepthBiasFactors(float fShadowSlopeScaleDepthBias, float fShadowDepthBias)
{
}

void CShaderAPI::BindVertexBuffer(int nStreamID, IVertexBuffer * pVertexBuffer, int nOffsetInBytes, int nFirstVertex, int nVertexCount, VertexFormat_t fmt, int nRepetitions)
{
}

void CShaderAPI::BindIndexBuffer(IIndexBuffer * pIndexBuffer, int nOffsetInBytes)
{
}

void CShaderAPI::Draw(MaterialPrimitiveType_t primitiveType, int nFirstIndex, int nIndexCount)
{
}

void CShaderAPI::PerformFullScreenStencilOperation(void)
{
}

void CShaderAPI::SetScissorRect(const int nLeft, const int nTop, const int nRight, const int nBottom, const bool bEnableScissor)
{
}

bool CShaderAPI::SupportsCSAAMode(int nNumSamples, int nQualityLevel)
{
	return false;
}

void CShaderAPI::InvalidateDelayedShaderConstants(void)
{
}

float CShaderAPI::GammaToLinear_HardwareSpecific(float fGamma) const
{
	return 0.0f;
}

float CShaderAPI::LinearToGamma_HardwareSpecific(float fLinear) const
{
	return 0.0f;
}

void CShaderAPI::SetLinearToGammaConversionTextures(ShaderAPITextureHandle_t hSRGBWriteEnabledTexture, ShaderAPITextureHandle_t hIdentityTexture)
{
}

ImageFormat CShaderAPI::GetNullTextureFormat(void)
{
	return ImageFormat();
}

void CShaderAPI::BindVertexTexture(VertexTextureSampler_t nSampler, ShaderAPITextureHandle_t textureHandle)
{
}

void CShaderAPI::EnableHWMorphing(bool bEnable)
{
}

void CShaderAPI::SetFlexWeights(int nFirstWeight, int nCount, const MorphWeight_t * pWeights)
{
}

void CShaderAPI::FogMaxDensity(float flMaxDensity)
{
}

void CShaderAPI::CreateTextures(ShaderAPITextureHandle_t * pHandles, int count, int width, int height, int depth, ImageFormat dstImageFormat, int numMipLevels, int numCopies, int flags, const char * pDebugName, const char * pTextureGroupName)
{
}

void CShaderAPI::AcquireThreadOwnership()
{
}

void CShaderAPI::ReleaseThreadOwnership()
{
}

bool CShaderAPI::SupportsNormalMapCompression() const
{
	return false;
}

void CShaderAPI::EnableBuffer2FramesAhead(bool bEnable)
{
}

void CShaderAPI::SetDepthFeatheringPixelShaderConstant(int iConstant, float fDepthBlendScale)
{
}

void CShaderAPI::PrintfVA(char * fmt, va_list vargs)
{
}

void CShaderAPI::Printf(PRINTF_FORMAT_STRING const char * fmt, ...)
{
}

float CShaderAPI::Knob(char * knobname, float * setvalue)
{
	return 0.0f;
}

void CShaderAPI::OverrideAlphaWriteEnable(bool bEnable, bool bAlphaWriteEnable)
{
}

void CShaderAPI::OverrideColorWriteEnable(bool bOverrideEnable, bool bColorWriteEnable)
{
}

void CShaderAPI::ClearBuffersObeyStencilEx(bool bClearColor, bool bClearAlpha, bool bClearDepth)
{
}

void CShaderAPI::CopyRenderTargetToScratchTexture(ShaderAPITextureHandle_t srcRt, ShaderAPITextureHandle_t dstTex, Rect_t * pSrcRect, Rect_t * pDstRect)
{
}

void CShaderAPI::LockRect(void ** pOutBits, int * pOutPitch, ShaderAPITextureHandle_t texHandle, int mipmap, int x, int y, int w, int h, bool bWrite, bool bRead)
{
}

void CShaderAPI::UnlockRect(ShaderAPITextureHandle_t texHandle, int mipmap)
{
}

void CShaderAPI::SetHeightClipMode(MaterialHeightClipMode_t heightClipMode)
{
}

void CShaderAPI::SetViewports(int nCount, const ShaderViewport_t * pViewports)
{
}

int CShaderAPI::GetViewports(ShaderViewport_t * pViewports, int nMax) const
{
	return 0;
}

void CShaderAPI::ClearBuffers(bool bClearColor, bool bClearDepth, bool bClearStencil, int renderTargetWidth, int renderTargetHeight)
{
}

void CShaderAPI::ClearColor3ub(unsigned char r, unsigned char g, unsigned char b)
{
}

void CShaderAPI::ClearColor4ub(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
}

void CShaderAPI::BindVertexShader(VertexShaderHandle_t hVertexShader)
{
}

void CShaderAPI::BindGeometryShader(GeometryShaderHandle_t hGeometryShader)
{
}

void CShaderAPI::BindPixelShader(PixelShaderHandle_t hPixelShader)
{
}

void CShaderAPI::SetRasterState(const ShaderRasterState_t & state)
{
}

bool CShaderAPI::SetMode(void * hwnd, int nAdapter, const ShaderDeviceInfo_t & info)
{
	return false;
}

void CShaderAPI::ChangeVideoMode(const ShaderDeviceInfo_t & info)
{
}

StateSnapshot_t CShaderAPI::TakeSnapshot()
{
	return StateSnapshot_t();
}

void CShaderAPI::TexMinFilter(ShaderTexFilterMode_t texFilterMode)
{
}

void CShaderAPI::TexMagFilter(ShaderTexFilterMode_t texFilterMode)
{
}

void CShaderAPI::TexWrap(ShaderTexCoordComponent_t coord, ShaderTexWrapMode_t wrapMode)
{
}

void CShaderAPI::CopyRenderTargetToTexture(ShaderAPITextureHandle_t textureHandle)
{
}

void CShaderAPI::Bind(IMaterial * pMaterial)
{
}

void CShaderAPI::FlushBufferedPrimitives()
{
}

IMesh * CShaderAPI::GetDynamicMesh(IMaterial * pMaterial, int nHWSkinBoneCount, bool bBuffered, IMesh * pVertexOverride, IMesh * pIndexOverride)
{
	return nullptr;
}

IMesh * CShaderAPI::GetDynamicMeshEx(IMaterial * pMaterial, VertexFormat_t vertexFormat, int nHWSkinBoneCount, bool bBuffered, IMesh * pVertexOverride, IMesh * pIndexOverride)
{
	return nullptr;
}

bool CShaderAPI::IsTranslucent(StateSnapshot_t id) const
{
	return false;
}

bool CShaderAPI::IsAlphaTested(StateSnapshot_t id) const
{
	return false;
}

bool CShaderAPI::UsesVertexAndPixelShaders(StateSnapshot_t id) const
{
	return false;
}

bool CShaderAPI::IsDepthWriteEnabled(StateSnapshot_t id) const
{
	return false;
}

VertexFormat_t CShaderAPI::ComputeVertexFormat(int numSnapshots, StateSnapshot_t * pIds) const
{
	return VertexFormat_t();
}

VertexFormat_t CShaderAPI::ComputeVertexUsage(int numSnapshots, StateSnapshot_t * pIds) const
{
	return VertexFormat_t();
}

void CShaderAPI::BeginPass(StateSnapshot_t snapshot)
{
}

void CShaderAPI::RenderPass(int nPass, int nPassCount)
{
}

void CShaderAPI::SetNumBoneWeights(int numBones)
{
}

void CShaderAPI::SetLight(int lightNum, const LightDesc_t & desc)
{
}

void CShaderAPI::SetLightingOrigin(Vector vLightingOrigin)
{
}

void CShaderAPI::SetAmbientLight(float r, float g, float b)
{
}

void CShaderAPI::SetAmbientLightCube(Vector4D cube[6])
{
}

void CShaderAPI::ShadeMode(ShaderShadeMode_t mode)
{
}

void CShaderAPI::CullMode(MaterialCullMode_t cullMode)
{
}

void CShaderAPI::ForceDepthFuncEquals(bool bEnable)
{
}

void CShaderAPI::OverrideDepthEnable(bool bEnable, bool bDepthEnable)
{
}

void CShaderAPI::SetHeightClipZ(float z)
{
}

void CShaderAPI::SetHeightClipMode(MaterialHeightClipMode_t heightClipMode)
{
}

void CShaderAPI::SetHeightClipMode(MaterialHeightClipMode_t heightClipMode)
{
}

void CShaderAPI::SetClipPlane(int index, const float * pPlane)
{
}

void CShaderAPI::EnableClipPlane(int index, bool bEnable)
{
}

void CShaderAPI::SetSkinningMatrices()
{
}

ImageFormat CShaderAPI::GetNearestSupportedFormat(ImageFormat fmt, bool bFilteringRequired) const
{
	return ImageFormat();
}

ImageFormat CShaderAPI::GetNearestRenderTargetFormat(ImageFormat fmt) const
{
	return ImageFormat();
}

bool CShaderAPI::DoRenderTargetsNeedSeparateDepthBuffer() const
{
	return false;
}

ShaderAPITextureHandle_t CShaderAPI::CreateTexture(int width, int height, int depth, ImageFormat dstImageFormat, int numMipLevels, int numCopies, int flags, const char * pDebugName, const char * pTextureGroupName)
{
	return ShaderAPITextureHandle_t();
}

void CShaderAPI::DeleteTexture(ShaderAPITextureHandle_t textureHandle)
{
}

ShaderAPITextureHandle_t CShaderAPI::CreateDepthTexture(ImageFormat renderTargetFormat, int width, int height, const char * pDebugName, bool bTexture)
{
	return ShaderAPITextureHandle_t();
}

bool CShaderAPI::IsTexture(ShaderAPITextureHandle_t textureHandle)
{
	return false;
}

bool CShaderAPI::IsTextureResident(ShaderAPITextureHandle_t textureHandle)
{
	return false;
}

void CShaderAPI::ModifyTexture(ShaderAPITextureHandle_t textureHandle)
{
}

void CShaderAPI::TexImage2D(int level, int cubeFaceID, ImageFormat dstFormat, int zOffset, int width, int height, ImageFormat srcFormat, bool bSrcIsTiled, void * imageData)
{
}

void CShaderAPI::TexSubImage2D(int level, int cubeFaceID, int xOffset, int yOffset, int zOffset, int width, int height, ImageFormat srcFormat, int srcStride, bool bSrcIsTiled, void * imageData)
{
}

void CShaderAPI::TexImageFromVTF(IVTFTexture * pVTF, int iVTFFrame)
{
}

bool CShaderAPI::TexLock(int level, int cubeFaceID, int xOffset, int yOffset, int width, int height, CPixelWriter & writer)
{
	return false;
}

void CShaderAPI::TexUnlock()
{
}

void CShaderAPI::TexSetPriority(int priority)
{
}

void CShaderAPI::BindTexture(Sampler_t sampler, ShaderAPITextureHandle_t textureHandle)
{
}

void CShaderAPI::SetRenderTarget(ShaderAPITextureHandle_t colorTextureHandle, ShaderAPITextureHandle_t depthTextureHandle)
{
}

void CShaderAPI::ClearBuffersObeyStencil(bool bClearColor, bool bClearDepth)
{
}

void CShaderAPI::ReadPixels(int x, int y, int width, int height, unsigned char * data, ImageFormat dstFormat)
{
}

void CShaderAPI::ReadPixels(Rect_t * pSrcRect, Rect_t * pDstRect, unsigned char * data, ImageFormat dstFormat, int nDstStride)
{
}

void CShaderAPI::FlushHardware()
{
}

void CShaderAPI::BeginFrame()
{
}

void CShaderAPI::EndFrame()
{
}

int CShaderAPI::SelectionMode(bool selectionMode)
{
	return 0;
}

void CShaderAPI::SelectionBuffer(unsigned int * pBuffer, int size)
{
}

void CShaderAPI::ClearSelectionNames()
{
}

void CShaderAPI::LoadSelectionName(int name)
{
}

void CShaderAPI::PushSelectionName(int name)
{
}

void CShaderAPI::PopSelectionName()
{
}

void CShaderAPI::ForceHardwareSync()
{
}

void CShaderAPI::ClearSnapshots()
{
}

void CShaderAPI::FogStart(float fStart)
{
}

void CShaderAPI::FogEnd(float fEnd)
{
}

void CShaderAPI::SetFogZ(float fogZ)
{
}

void CShaderAPI::SceneFogColor3ub(unsigned char r, unsigned char g, unsigned char b)
{
}

void CShaderAPI::GetSceneFogColor(unsigned char * rgb)
{
}

void CShaderAPI::SceneFogMode(MaterialFogMode_t fogMode)
{
}

bool CShaderAPI::CanDownloadTextures() const
{
	return false;
}

void CShaderAPI::ResetRenderState(bool bFullReset)
{
}

int CShaderAPI::GetCurrentDynamicVBSize(void)
{
	return 0;
}

void CShaderAPI::DestroyVertexBuffers(bool bExitingLevel)
{
}

void CShaderAPI::EvictManagedResources()
{
}

void CShaderAPI::SetAnisotropicLevel(int nAnisotropyLevel)
{
}

void CShaderAPI::SyncToken(const char * pToken)
{
}

void CShaderAPI::SetStandardVertexShaderConstants(float fOverbright)
{
}

ShaderAPIOcclusionQuery_t CShaderAPI::CreateOcclusionQueryObject(void)
{
	return ShaderAPIOcclusionQuery_t();
}

void CShaderAPI::DestroyOcclusionQueryObject(ShaderAPIOcclusionQuery_t)
{
}

void CShaderAPI::BeginOcclusionQueryDrawing(ShaderAPIOcclusionQuery_t)
{
}

void CShaderAPI::EndOcclusionQueryDrawing(ShaderAPIOcclusionQuery_t)
{
}

int CShaderAPI::OcclusionQuery_GetNumPixelsRendered(ShaderAPIOcclusionQuery_t hQuery, bool bFlush)
{
	return 0;
}

void CShaderAPI::SetFlashlightState(const FlashlightState_t & state, const VMatrix & worldToTexture)
{
}

void CShaderAPI::ClearVertexAndPixelShaderRefCounts()
{
}

void CShaderAPI::PurgeUnusedVertexAndPixelShaders()
{
}

void CShaderAPI::DXSupportLevelChanged()
{
}

void CShaderAPI::EnableUserClipTransformOverride(bool bEnable)
{
}

void CShaderAPI::UserClipTransform(const VMatrix & worldToView)
{
}

MorphFormat_t CShaderAPI::ComputeMorphFormat(int numSnapshots, StateSnapshot_t * pIds) const
{
	return MorphFormat_t();
}

void CShaderAPI::SetRenderTargetEx(int nRenderTargetID, ShaderAPITextureHandle_t colorTextureHandle, ShaderAPITextureHandle_t depthTextureHandle)
{
}

void CShaderAPI::CopyRenderTargetToTextureEx(ShaderAPITextureHandle_t textureHandle, int nRenderTargetID, Rect_t * pSrcRect, Rect_t * pDstRect)
{
}

void CShaderAPI::CopyTextureToRenderTargetEx(int nRenderTargetID, ShaderAPITextureHandle_t textureHandle, Rect_t * pSrcRect, Rect_t * pDstRect)
{
}

void CShaderAPI::HandleDeviceLost()
{
}

void CShaderAPI::EnableLinearColorSpaceFrameBuffer(bool bEnable)
{
}

void CShaderAPI::SetFullScreenTextureHandle(ShaderAPITextureHandle_t h)
{
}

void CShaderAPI::SetFloatRenderingParameter(int parm_number, float value)
{
}

void CShaderAPI::SetIntRenderingParameter(int parm_number, int value)
{
}

void CShaderAPI::SetVectorRenderingParameter(int parm_number, Vector const & value)
{
}

float CShaderAPI::GetFloatRenderingParameter(int parm_number) const
{
	return 0.0f;
}

int CShaderAPI::GetIntRenderingParameter(int parm_number) const
{
	return 0;
}

Vector CShaderAPI::GetVectorRenderingParameter(int parm_number) const
{
	return Vector();
}

void CShaderAPI::SetFastClipPlane(const float * pPlane)
{
}

void CShaderAPI::EnableFastClip(bool bEnable)
{
}
