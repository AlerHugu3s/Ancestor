workspace "Ancestor"
    architecture "x64"

    startproject "Sandbox"
    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Ancestor/vendor/GLFW/include"
IncludeDir["Glad"] = "Ancestor/vendor/Glad/include"
IncludeDir["ImGui"] = "Ancestor/vendor/imgui"
IncludeDir["glm"] = "Ancestor/vendor/glm"
IncludeDir["stb_image"] = "Ancestor/vendor/stb_image"
IncludeDir["Assimp"] = "Ancestor/vendor/AssimpWithPremake/include"

group "Dependencies"
    include "Ancestor/vendor/Glad"
    include "Ancestor/vendor/GLFW"
    include "Ancestor/vendor/imgui"
	include "Ancestor/vendor/AssimpWithPremake"
group ""

project "Ancestor"
    location "Ancestor"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir ("bin-int/"..outputdir.."/%{prj.name}")

    pchheader "acpch.h"
    pchsource "Ancestor/src/acpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/std_image/**.h",
        "%{prj.name}/vendor/std_image/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    defines 
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
		"%{IncludeDir.Assimp}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
		"Assimp",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "AC_PLATFORM_WINDOWS",
            "AC_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "AC_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "AC_RELEATSE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "AC_DIST"
        runtime "Release"
        optimize "on"
    
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir ("bin-int/"..outputdir.."/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Ancestor/vendor/spdlog/include",
        "Ancestor/vendor/AssimpWithPremake/include",
        "Ancestor/src",
        "Ancestor/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
		"Assimp",
        "Ancestor"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "AC_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "AC_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "AC_RELEATSE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "AC_DIST"
        runtime "Release"
        optimize "on"
    