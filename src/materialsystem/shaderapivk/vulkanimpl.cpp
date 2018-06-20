#include "vulkanimpl.h"

#include "tier0/memdbgon.h"

void* VKAPI_PTR myVk_OnAlloc(void* pUserData, size_t size, size_t alignment, VkSystemAllocationScope allocationScope)
{
	return MemAlloc_AllocAligned(size, alignment);
}

void* VKAPI_PTR myVk_OnRealloc(void* pUserData, void* pOriginal, size_t size, size_t alignment, VkSystemAllocationScope allocationScope)
{
	return MemAlloc_ReallocAligned(pOriginal, size, alignment);
}

void VKAPI_PTR myVk_OnFree(void* pUserData, void* pMemory)
{
	return MemAlloc_Free(pMemory);
}

void VKAPI_PTR myVk_OnAllocNote(void* pUserData, size_t size, VkInternalAllocationType allocationType, VkSystemAllocationScope allocationScope)
{
}

void VKAPI_PTR myVk_OnFreeNote(void* pUserData, size_t size, VkInternalAllocationType allocationType, VkSystemAllocationScope allocationScope)
{
}

VkAllocationCallbacks g_AllocCallbacks
{
	nullptr, 
	myVk_OnAlloc,
	myVk_OnRealloc,
	myVk_OnFree,
	myVk_OnAllocNote,
	myVk_OnFreeNote
};

VkAllocationCallbacks* g_pAllocCallbacks = &g_AllocCallbacks;

uint32_t numValidationLayers = 0;
const char* const * validationLayers = nullptr;

const char * const * GetValidationLayers()
{
	return nullptr;
}

uint32_t GetValidationLayerCount()
{
	return uint32_t();
}

void InitValidationLayers()
{
}
