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
IncludeDir["glad"] = "Legio/vendor/Glad/include"
IncludeDir["ImGui"] = "Legio/vendor/imgui"
IncludeDir["glm"] = "Legio/vendor/glm"

include "Legio/vendor/GLFW"
include "Legio/vendor/Glad"
include "Legio/vendor/imgui"

project "Legio"
    location "Legio"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    
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
        IncludeDir.GLFW,
        IncludeDir.glad,
        IncludeDir.ImGui,
        IncludeDir.glm
    }

    links
    {
        "GLFW",
        "glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"    
        
        defines
        {
            "LG_PLATFORM_WINDOWS",
            "LG_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "LG_DEBUG"
        buildoptions "/MDd"
        symbols "on"

    filter "configurations:Release"
        defines "LG_RELEASE"
        buildoptions "/MD"
        optimize "on"

    filter "configurations:Dist"
        defines "LG_DIST"
        buildoptions "/MD"
        optimize "on"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

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
        "Legio/src",
		IncludeDir.glm
    }

    links
    {
        "Legio"
    }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"    
        
        defines {
            "LG_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines {
            "LG_DEBUG",
            "LG_ENABLE_ASSERTS"
        }
        buildoptions "/MDd"
        symbols "on"

    filter "configurations:Release"
        defines "LG_RELEASE"
        buildoptions "/MD"
        optimize "on"

    filter "configurations:Dist"
        defines "LG_DIST"
        buildoptions "/MD"
        optimize "on"