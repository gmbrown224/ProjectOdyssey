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
IncludeDir["imgui"] = "Titus-Engine/vendor/imgui"
IncludeDir["glm"] = "Titus-Engine/vendor/glm"

group "Dependencies"
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

	libdirs {
		"Titus-Engine/vendor/SDL/build/Release"
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
		"%{IncludeDir.glm}",
		"%{IncludeDir.imgui}",
		"%{prj.name}/vendor/SDL/include",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/stb"
	}

	links 
	{ 
		"imgui",
		"SDL3",
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
			"TE_PLATFORM_WINDOWS",
			"TE_ENABLE_ASSERTS",
			"TE_BUILD_DLL",
			"_WINDLL"
		}

		postbuildcommands
		{
			"copy /B /Y ..\\bin\\" .. outputdir .. "\\Titus-Engine\\Titus-Engine.dll ..\\bin\\" .. outputdir .. "\\TITEN\\ > nul",
			"copy /B /Y ..\\Titus-Engine\\vendor\\SDL\\build\\Release\\SDL3.dll ..\\bin\\" .. outputdir .. "\\Titus-Engine\\ > nul",
			"copy /B /Y ..\\Titus-Engine\\vendor\\SDL\\build\\Release\\SDL3.dll ..\\bin\\" .. outputdir .. "\\TITEN\\ > nul"
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
		"Titus-Engine/vendor/SDL/include",
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