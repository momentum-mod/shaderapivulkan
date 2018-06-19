#pragma once

#include <vulkan/vulkan.hpp>

extern VkAllocationCallbacks* g_pAllocCallbacks;

extern const char* const* GetValidationLayers();
extern uint32_t GetValidationLayerCount();

void InitValidationLayers();