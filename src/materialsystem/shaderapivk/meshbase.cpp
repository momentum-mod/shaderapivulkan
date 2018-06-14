#include "meshbase.h"

void CVertexBufferBase::Spew(int nVertexCount, const VertexDesc_t & desc)
{
}

void CVertexBufferBase::ValidateData(int nVertexCount, const VertexDesc_t & desc)
{
}

CVertexBufferBase::CVertexBufferBase(const char * pBudgetGroupName)
{
}

CVertexBufferBase::~CVertexBufferBase()
{
}

void CVertexBufferBase::PrintVertexFormat(VertexFormat_t vertexFormat)
{
}

void CVertexBufferBase::ComputeVertexDescription(unsigned char * pBuffer, VertexFormat_t vertexFormat, VertexDesc_t & desc)
{
}

int CVertexBufferBase::VertexFormatSize(VertexFormat_t vertexFormat)
{
	return 0;
}

void CIndexBufferBase::Spew(int nIndexCount, const IndexDesc_t & desc)
{
}

void CIndexBufferBase::ValidateData(int nIndexCount, const IndexDesc_t & desc)
{
}

CIndexBufferBase::CIndexBufferBase(const char * pBudgetGroupName)
{
}

CMeshBase::CMeshBase()
{
}

CMeshBase::~CMeshBase()
{
}
