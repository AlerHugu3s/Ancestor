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

group "Dependencies"
    include "Ancestor/vendor/GLFW"
    include "Ancestor/vendor/Glad"
    include "Ancestor/vendor/imgui"
group ""

project "Ancestor"
    location "Ancestor"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir ("bin-int/"..outputdir.."/%{prj.name}")

    pchheader "acpch.h"
    pchsource "Ancestor/src/acpch.cpp"

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
        "%{prj.name}/vendor/spdlog/include",
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
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "AC_PLATFORM_WINDOWS",
            "AC_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .."/Sandbox/\"")
        }

    filter "configurations:Debug"
        defines "AC_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "AC_RELEATSE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "AC_DIST"
        runtime "Release"
        optimize "On"
    
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

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
        "Ancestor/src",
        "Ancestor/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "ImGui",
        "Ancestor"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "AC_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "AC_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "AC_RELEATSE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "AC_DIST"
        runtime "Release"
        optimize "On"
    