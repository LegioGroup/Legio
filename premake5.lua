--premake5.lua

workspace "Legio"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Legio/vendor/GLFW/include"

include "Legio/vendor/GLFW"

project "Legio"
    location "Legio"
    kind "SharedLib"
    language "C++"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

    pchheader "lgpch.h"
    pchsource "Legio/src/lgpch.cpp"
    
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        IncludeDir.GLFW
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
            "LG_PLATFORM_WINDOWS",
            "LG_BUILD_DLL",
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "LG_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "LG_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "LG_DIST"
        optimize "On"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Legio/vendor/spdlog/include",
        "Legio/src"
    }

    links
    {
        "Legio"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"    
        
        defines
        {
            "LG_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "LG_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "LG_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "LG_DIST"
        optimize "On"