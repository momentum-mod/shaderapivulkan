#include "shaderutil.h"

bool CShaderUtil::ConvertImageFormat(unsigned char * src, ImageFormat srcImageFormat, unsigned char * dst, ImageFormat dstImageFormat, int width, int height, int srcStride, int dstStride)
{
	return false;
}

CShaderUtil::CShaderUtil()
{
}

CShaderUtil::~CShaderUtil()
{
}

bool CShaderUtil::Connect(CreateInterfaceFn factory)
{
	return false;
}

void CShaderUtil::Disconnect()
{
}

void * CShaderUtil::QueryInterface(const char * pInterfaceName)
{
	return nullptr;
}

InitReturnVal_t CShaderUtil::Init()
{
	return InitReturnVal_t();
}

void CShaderUtil::Shutdown()
{
}

MaterialSystem_Config_t & CShaderUtil::GetConfig()
{
	// TODO: hier Rückgabeanweisung eingeben
}

int CShaderUtil::GetMemRequired(int width, int height, int depth, ImageFormat format, bool mipmap)
{
	return 0;
}

const ImageFormatInfo_t & CShaderUtil::ImageFormatInfo(ImageFormat fmt) const
{
	// TODO: hier Rückgabeanweisung eingeben
}

void CShaderUtil::BindStandardTexture(Sampler_t sampler, StandardTextureId_t id)
{
}

void CShaderUtil::GetLightmapDimensions(int * w, int * h)
{
}

void CShaderUtil::ReleaseShaderObjects()
{
}

void CShaderUtil::RestoreShaderObjects(CreateInterfaceFn shaderFactory, int nChangeFlags)
{
}

bool CShaderUtil::IsInStubMode()
{
	return false;
}

bool CShaderUtil::InFlashlightMode() const
{
	return false;
}

void CShaderUtil::NoteAnisotropicLevel(int currentLevel)
{
}

bool CShaderUtil::InEditorMode() const
{
	return false;
}

MorphFormat_t CShaderUtil::GetBoundMorphFormat()
{
	return MorphFormat_t();
}

ITexture * CShaderUtil::GetRenderTargetEx(int nRenderTargetID)
{
	return nullptr;
}

void CShaderUtil::DrawClearBufferQuad(unsigned char r, unsigned char g, unsigned char b, unsigned char a, bool bClearColor, bool bClearAlpha, bool bClearDepth)
{
}

bool CShaderUtil::OnDrawMesh(IMesh * pMesh, int firstIndex, int numIndices)
{
	return false;
}

bool CShaderUtil::OnDrawMesh(IMesh * pMesh, CPrimList * pLists, int nLists)
{
	return false;
}

bool CShaderUtil::OnSetFlexMesh(IMesh * pStaticMesh, IMesh * pMesh, int nVertexOffsetInBytes)
{
	return false;
}

bool CShaderUtil::OnSetColorMesh(IMesh * pStaticMesh, IMesh * pMesh, int nVertexOffsetInBytes)
{
	return false;
}

bool CShaderUtil::OnSetPrimitiveType(IMesh * pMesh, MaterialPrimitiveType_t type)
{
	return false;
}

bool CShaderUtil::OnFlushBufferedPrimitives()
{
	return false;
}

void CShaderUtil::SyncMatrices()
{
}

void CShaderUtil::SyncMatrix(MaterialMatrixMode_t)
{
}

void CShaderUtil::BindStandardVertexTexture(VertexTextureSampler_t sampler, StandardTextureId_t id)
{
}

void CShaderUtil::GetStandardTextureDimensions(int * pWidth, int * pHeight, StandardTextureId_t id)
{
}

int CShaderUtil::MaxHWMorphBatchCount() const
{
	return 0;
}

void CShaderUtil::GetCurrentColorCorrection(ShaderColorCorrectionInfo_t * pInfo)
{
}

void CShaderUtil::OnThreadEvent(uint32 threadEvent)
{
}

MaterialThreadMode_t CShaderUtil::GetThreadMode()
{
	return MaterialThreadMode_t();
}

bool CShaderUtil::IsRenderThreadSafe()
{
	return false;
}

void CShaderUtil::UncacheUnusedMaterials(bool bRecomputeStateSnapshots)
{
}
