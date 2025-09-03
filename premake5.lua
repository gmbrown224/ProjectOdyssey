--
-- Titus Engine & TITEN App Makefile
--

workspace "Titus-Engine"
	architecture "x64"
	startproject "TITEN"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLAD"] = "Titus-Engine/vendor/GLAD/include"
IncludeDir["GLFW"] = "Titus-Engine/vendor/GLFW/include"
IncludeDir["imgui"] = "Titus-Engine/vendor/imgui"
IncludeDir["glm"] = "Titus-Engine/vendor/glm"
IncludeDir["SDL"] = "Titus-Engine/vendor/SDL/include/SDL3"

group "Dependencies"
	include "Titus-Engine/vendor/GLAD"
	include "Titus-Engine/vendor/GLFW"
	include "Titus-Engine/vendor/imgui"

group ""

-- Build Engine Project

project "Titus-Engine"
	location "Titus-Engine"
	kind "SharedLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	pchheader "TEpch.h"
	pchsource "Titus-Engine/src/TEpch.cpp"

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.imgui}",
		"%{prj.name}/vendor/SDL/include/SDL3",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/stb"
	}

	links 
	{ 
		"GLAD",
		"GLFW",
		"imgui",
		"opengl32.lib"
	}

	buildoptions
	{
		"/utf-8"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GLFW_INCLUDE_NONE",
			"TE_PLATFORM_WINDOWS",
			"TE_ENABLE_ASSERTS",
			"TE_BUILD_DLL",
			"_WINDLL"
		}

	filter "configurations:Debug"
		defines "TE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "TE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "TE_DIST"
		runtime "Release"
		optimize "On"

-- Build TITEN Project

project "TITEN"
	location "TITEN"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Titus-Engine/src",
		"Titus-Engine/vendor/imgui",
		"Titus-Engine/vendor/SDL/include/SDL3",
		"Titus-Engine/vendor/spdlog/include",
		"Titus-Engine/vendor/glm"
	}

	links
	{
		"Titus-Engine"
	}

	buildoptions
	{
		"/utf-8"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"TE_PLATFORM_WINDOWS",
			"_WINDLL"
		}

	filter "configurations:Debug"
		defines "TE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "TE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "TE_DIST"
		runtime "Release"
		optimize "On"