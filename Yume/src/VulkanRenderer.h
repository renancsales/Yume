#pragma once


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
// Check only the generic errors
#include <stdexcept>
#include <vector>
#include <set>
#include <algorithm>
#include <array>

// stb_image
#include <stb_image.h>


#include "Mesh.h"
#include "MeshModel.h"
#include "Scene.h"
#include "Utils.h"


// Enable validation layers only in debug mode
#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif



class VulkanRenderer
{
public:
	//VulkanRenderer() = default;
	//VulkanRenderer(const VulkanRenderer&) = default;
	//VulkanRenderer& operator=(const VulkanRenderer&) = default;

	

public:
	static int Init(GLFWwindow* window);

	static void SetScene();
	static void SceneUpdate(float ts);

	static void UpdateModel(uint32_t meshObjectIndex, glm::mat4& newModel);

	static void Draw();
	static void CleanUp();

private:
	// Create functions
	static void CreateInstance();
	static void CreateLogicalDevice();
	static void CreateSurface();
	static void CreateSwapChain();
	static void CreateRenderPass();
	static void CreateDescriptorSetLayout();
	static void CreateGraphicsPipeline();
	static void CreateDepthBufferImage();
	static void CreateColorBufferImage();
	static void CreateFramebuffers();
	static void CreateCommandPool();
	static void CreateCommandBuffers();
	static void CreateSynchronization();

	static void CreateTextureSampler();

	static void CreateUniformBuffers();
	static void CreateDescriptorPool();
	static void CreateDescriptorSets();
	static void CreateInputDescriptorSets();

	static void UpdateUniformBuffers(uint32_t imageIndex);

	// Record functions
	static void RecordCommands(uint32_t currentImageIndex);

	// Get functions
	static void GetPhysicalDevice();

	// - Allocate functions
	static void AllocateDynamicBufferTransferSpace();

	// Support functions
	// -- Check functions
	static bool CheckInstanceExtensionSupport(std::vector<const char*>* checkExtensions);
	static bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
	static bool CheckDeviceSuitable(VkPhysicalDevice device);
	// -- getter functions
	static QueueFamilyIndices GetQueueFamilies(VkPhysicalDevice device);
	static SwapChainDetails GetSwapChainDetails(VkPhysicalDevice device);


	// -- pick functions
	static VkSurfaceFormatKHR ChooseBestSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& formats);
	static VkPresentModeKHR ChooseBestPresentationMode(const std::vector< VkPresentModeKHR>& presentationModes);
	static VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& surfaceCapabilities);
	static VkFormat ChooseSupportedFormat(const std::vector<VkFormat>& formats, VkImageTiling tiling, VkFormatFeatureFlags featureFlags);

	// validation layer
	static bool CheckValidationLayerSupport();

	// -- Create functions
	static VkImage CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling,
		VkImageUsageFlags usageFlags, VkMemoryPropertyFlags propFlags, VkDeviceMemory* imageMemory);
	static VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
	static VkShaderModule CreateShaderModule(const std::vector<char>& code);

	static int CreateTextureImage(const std::string& filepath);
	static int CreateTexture(const std::string& filepath);
	static int CreateTextureDescriptor(VkImageView textureImage);

	static void CreateMeshModel(const std::string& filepath);

	// Loader-functions
	static stbi_uc* LoadTextureFile(const std::string& fileName, int* width, int* height, VkDeviceSize* imageSize);

};

