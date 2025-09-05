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
IncludeDir["SDL"] = "Titus-Engine/vendor/SDL"

group "Dependencies"
	include "Titus-Engine/vendor/imgui"
	include "Titus-Engine/vendor/SDL"

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
		"C:/VulkanSDK/1.4.321.1/Lib"
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
		"%{IncludeDir.SDL}/include",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/stb",
		"%{prj.name}/vendor/Vulkan-Headers/include"
	}

	links 
	{ 
		"imgui",
		"SDL"
	}

	buildoptions
	{
		"/utf-8"
	}

	postbuildcommands {
		'copy /Y "%{cfg.targetdir}\\Titus-Engine.dll" "%{wks.location}\\bin\\' .. outputdir .. '\\TITEN\\" > nul'
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"TE_PLATFORM_WINDOWS",
			"TE_ENABLE_ASSERTS",
			"TE_BUILD_DLL"
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
		"Titus-Engine/vendor/spdlog/include"
	}

	links
	{
		"Titus-Engine"
	}

	dependson
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
			"TE_PLATFORM_WINDOWS"
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