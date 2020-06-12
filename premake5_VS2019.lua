workspace "IMAT3905"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

group "IMAT3905"

project "Sandbox"
	location "sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"
	cppdialect "C++17"
	systemversion "latest"
		
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/include",
		"vendor/renderer/include",
		"vendor/glm/",
		"vendor/spdlog/include",
		"vendor/glfw/include",
		"vendor/Glad/include",
		"vendor/stb_image"
	}

	links 
	{
		"GLFW",
		"Glad"
	}
	
	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		links
		{
			"./vendor/renderer/lib/IMAT3905_2017_DEBUG.lib"
		}


	filter "configurations:Release"
		runtime "Release"
		optimize "On"
		links
		{
			"./vendor/renderer/lib/IMAT3905_2017_RELEASE.lib"
		}
group "Vendor"
	include "vendor/glfw"
	include "vendor/Glad"

