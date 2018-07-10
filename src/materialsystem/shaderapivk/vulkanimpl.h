#pragma once

// MOM_VK_TODO: Make this the correct platform define
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.hpp>

extern VkAllocationCallbacks* g_pAllocCallbacks;

extern const char* const* GetValidationLayers();
extern uint32_t GetValidationLayerCount();

void InitValidationLayers();