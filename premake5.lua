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
IncludeDir["Glad"] = "Ancestor/vendor/Glad/include"
IncludeDir["ImGui"] = "Ancestor/vendor/imgui"

include "Ancestor/vendor/GLFW"
include "Ancestor/vendor/Glad"
include "Ancestor/vendor/imgui"

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
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "Off"
        systemversion "latest"

        defines
        {
            "AC_PLATFORM_WINDOWS",
            "AC_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .."/Sandbox")
        }

    filter "configurations:Debug"
        defines "AC_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "AC_RELEATSE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "AC_DIST"
        buildoptions "/MD"
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
        staticruntime "Off"
        systemversion "latest"

        defines
        {
            "AC_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "AC_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "AC_RELEATSE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "AC_DIST"
        buildoptions "/MD"
        optimize "On"
    