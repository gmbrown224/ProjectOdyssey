--
-- Titus Engine & Sandbox App Makefile
--

workspace "Titus-Engine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Titus-Engine/vendor/GLFW/include"
IncludeDir["GLAD"] = "Titus-Engine/vendor/GLAD/include"

include "Titus-Engine/vendor/GLFW"
include "Titus-Engine/vendor/GLAD"

-- Build Engine Project

project "Titus-Engine"
	location "Titus-Engine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	pchheader "TEpch.h"
	pchsource "Titus-Engine/src/TEpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}"
	}

	links 
	{ 
		"GLFW",
		"GLAD",
		"opengl32.lib"
	}

	buildoptions
	{
		"/utf-8",
		"/MD"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "Off"
		systemversion "latest"

		defines
		{
			"TE_PLATFORM_WINDOWS",
			"TE_ENABLE_ASSERTS",
			"TE_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"_WINDLL"
		}

		postbuildcommands
		{
			"copy /B /Y ..\\bin\\" .. outputdir .. "\\Titus-Engine\\Titus-Engine.dll ..\\bin\\" .. outputdir .. "\\Sandbox\\ > nul"
		}

	filter "configurations:Debug"
		defines "TE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "TE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "TE_DIST"
		optimize "On"

-- Build Sandbox Project

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"Titus-Engine/vendor/spdlog/include"
	}

	links
	{
		"Titus-Engine"
	}

	buildoptions
	{
		"/utf-8",
		"/MD"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "Off"
		systemversion "latest"

		defines
		{
			"TE_PLATFORM_WINDOWS",
			"_WINDLL"
		}

	filter "configurations:Debug"
		defines "TE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "TE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "TE_DIST"
		optimize "On"