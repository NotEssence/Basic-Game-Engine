workspace "BasicGE"
	architecture "x64"
	startproject "BasicGE"

	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include dirs
IncludeDir = {}
IncludeDir["GLFW"] = "BasicGE/vender/GLFW/include"
IncludeDir["Glad"] = "BasicGE/vender/Glad/include"
IncludeDir["ImGui"] = "BasicGE/vender/imgui"
IncludeDir["glm"] = "BasicGE/vender/glm"


include "BasicGE/vender/GLFW"
include "BasicGE/vender/Glad"
include "BasicGE/vender/imgui"

project "BasicGE"
	location "BasicGE"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "bgepch.h"
	pchsource "BasicGE/src/bgepch.cpp"

	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h",
		"%{prj.name}/vender/glm/glm/**.hpp",
		"%{prj.name}/vender/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vender/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links 
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"BGE_WIN64",
			"BGE_BUILD_STATIC",
			"BGE_ENABLE_ASSERTIONS"
		}

	filter "configurations:Debug"
		defines "BGE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "BGE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "BGE_DIST"
		runtime "Release"
		optimize "on"

project "BGE_App"
	location "BGE_App"
	kind "ConsoleApp"
	language "C++"
	staticruntime "On"
	cppdialect "C++17"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h"
	}

	includedirs
	{
		"BasicGE/vender/spdlog/include",
		"BasicGE/src",
		"%{IncludeDir.glm}",
		"BasicGE/vender",
	}

	links
	{
		"BasicGE"
	}

	defines 
	{
		"BGE_ENABLE_ASSERTIONS"
	}

	filter "system:windows"
		systemversion "latest"

		defines	"BGE_WIN64"

	filter "configurations:Debug"
		defines "BGE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "BGE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "BGE_DIST"
		runtime "Release"
		optimize "on"
