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
IncludeDir["GLAD"] = "Titus-Engine/vendor/GLAD/include"
IncludeDir["GLFW"] = "Titus-Engine/vendor/GLFW/include"
IncludeDir["imgui"] = "Titus-Engine/vendor/imgui"

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
	staticruntime "Off"

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
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.imgui}",
		"%{prj.name}/vendor/spdlog/include"
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
		cppdialect "C++20"
		systemversion "latest"

		defines
		{
			"GLFW_INCLUDE_NONE",
			"TE_PLATFORM_WINDOWS",
			"TE_ENABLE_ASSERTS",
			"TE_BUILD_DLL",
			"_WINDLL"
		}

		postbuildcommands
		{
			"copy /B /Y ..\\bin\\" .. outputdir .. "\\Titus-Engine\\Titus-Engine.dll ..\\bin\\" .. outputdir .. "\\Sandbox\\ > nul"
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

-- Build Sandbox Project

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
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
		"Titus-Engine/vendor/spdlog/include"
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
		cppdialect "C++20"
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