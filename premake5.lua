workspace "Ancestor"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Ancestor/vendor/GLFW/include"

include "Ancestor/vendor/GLFW"

project "Ancestor"
    location "Ancestor"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir ("bin-int/"..outputdir.."/%{prj.name}")

    pchheader "acpch.h"
    pchsource "Ancestor/src/acpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}"
    }

    links
    {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "AC_PLATFORM_WINDOWS",
            "AC_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .."/Sandbox")
        }

    filter "configurations:Debug"
        defines "AC_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "AC_RELEATSE"
        optimize "On"

    filter "configurations:Dist"
        defines "AC_DIST"
        optimize "On"
    
project "Sandbox"

location "Sandbox"
    kind "ConsoleApp"
    language "C++"

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
        "Ancestor/src"
    }

    links
    {
        "Ancestor"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "AC_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "AC_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "AC_RELEATSE"
        optimize "On"

    filter "configurations:Dist"
        defines "AC_DIST"
        optimize "On"
    