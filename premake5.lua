projectName = "Yume"
workspace "Yume"
	architecture "x64"
	startproject  "Yume"
	
	configurations
	{
		"Debug",
		"Release",
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


-- Include directories relative to root folder (sol. directory)
IncludeDir = {}
VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"

project "Yume"
	location "Yume"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
		
	-- Additional library directories
	libdirs { 	"%{prj.name}/vendor/ASSIMP/lib",
				"%{prj.name}/vendor/GLFW/lib",
				"%{LibraryDir.VulkanSDK}"
			}
	

				
	-- OpenMP support
	-- buildoptions { "/openmp" }
	
	defines 
	{
		"NDEBUG", "_CONSOLE", 
	}
	
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/ASSIMP/include",
		"%{prj.name}/vendor/GLFW/include",
		"%{prj.name}/vendor/GLM",
		"%{prj.name}/vendor/stb_image",
		"%{IncludeDir.VulkanSDK}",
	}
	
	links {	"glfw3.lib",
			"assimp-vc142-mt.lib",
			"%{Library.Vulkan}"}

	-- Filter: Configurations only applied to specific platforms
	filter "system:windows"
		systemversion "latest"
		postbuildcommands {
		"{COPY} ..\\%{prj.name}\\vendor\\ASSIMP\\lib\\assimp-vc142-mt.dll %{cfg.targetdir}"
		}
		
	filter "configurations:Debug"
		defines { "NDEBUG" }
		runtime "Debug"
		symbols "On"
		
	  
	filter "configurations:Release"
		defines { "_RELEASE" }
		runtime "Release"
		optimize "On"
		symbols "On"
		 
