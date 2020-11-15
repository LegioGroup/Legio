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

include "Legio/vendor/GLFW"
include "Legio/vendor/Glad"
include "Legio/vendor/imgui"

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
        IncludeDir.GLFW,
        IncludeDir.glad,
        IncludeDir.ImGui
    }

    links
    {
        "GLFW",
        "glad",
        "ImGui",
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
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "LG_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "LG_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "LG_DIST"
        buildoptions "/MD"
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
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "LG_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "LG_DIST"
        buildoptions "/MD"
        optimize "On"