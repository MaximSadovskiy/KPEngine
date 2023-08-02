workspace "KPEngine"
    architecture "x64"
	startproject "ExampleApp"
    configurations 
    {
        "Debug",
        "Release",
		"Dist"
    }
    platforms 
    {
        "x64"
    }
	flags
	{
		"MultiProcessorCompile"
	}

	filter "configurations:Debug"
        defines { "__KPE_DEBUG__" }
		runtime "Debug"
		optimize "Off"
        symbols "On"
    
    filter "configurations:Release"
        defines { "__KPE_RELEASE__" }
		runtime "Release"
		optimize "Speed"

    filter "configurations:Dist"
        defines { "__KPE_DIST__" }
		runtime "Release"
        optimize "Speed"

    filter "platforms:x64"
        architecture = "64"

outputdir = "%{cfg.buildcfg}-x%{architecture}"
engineName = "KPEngine"

project (""..engineName.."")
    location (""..engineName.."")
    kind "StaticLib"
    language "C++"
	cppdialect "C++17"
    systemversion "latest"
    staticruntime "Off"
    targetdir("%{wks.location}/"..engineName.."/bin/" ..outputdir.. "/")
    objdir("%{wks.location}/"..engineName.."/bin-obj/" ..outputdir.. "/")
	

	includedirs
    {
        ""..engineName.."/vendor/glfw/include/",
        ""..engineName.."/vendor/glew/include/",
        ""..engineName.."/vendor/spdlog/include/",
	--	""..engineName.."/vendor/imgui/include/",
		""..engineName.."/src/core/",
    }

    libdirs
    {
        "%{wks.location}/"..engineName.."/vendor/glfw/lib",
        "%{wks.location}/"..engineName.."/vendor/glew/lib",
    }
    links
    {
        "glew32s.lib",
        "glfw3_mt.lib",
        "opengl32.lib",
    }

    files 
    {
        "%{wks.location}/"..engineName.."/src/**.cpp",
        "%{wks.location}/"..engineName.."/src/**.h",
        "%{wks.location}/"..engineName.."/vendor/glfw/include/**.cpp",
        "%{wks.location}/"..engineName.."/vendor/glfw/include/**.h",
        "%{wks.location}/"..engineName.."/vendor/glew/include/**.cpp",
        "%{wks.location}/"..engineName.."/vendor/glew/include/**.h",
        "%{wks.location}/"..engineName.."/vendor/spdlog/include/**.cpp",
        "%{wks.location}/"..engineName.."/vendor/spdlog/include/**.h",
	--	"%{wks.location}/"..engineName.."/vendor/imgui/include/**.cpp",
    --	"%{wks.location}/"..engineName.."/vendor/imgui/include/**.h",
    }

	pchheader "KpePch.h"
	pchsource (""..engineName.."/src/core/KpePch.cpp")

    defines
    {
        "GLEW_STATIC",
    }

project "ExampleApp"
    location "ExampleApp"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    systemversion "latest"
    targetdir("%{wks.location}/ExampleApp/bin/" ..outputdir.. "/")
    objdir("%{wks.location}/ExampleApp/bin-obj/" ..outputdir.. "/")
    
    includedirs
    {
        "%{wks.location}/%{engineName}/src",
        "%{wks.location}/%{engineName}/vendor/glfw/include/",
        "%{wks.location}/%{engineName}/vendor/glew/include/",
        "%{wks.location}/%{engineName}/vendor/spdlog/include/",
    }
    
    links
    {
        "%{engineName}"
    }
        
    files
    {
        "%{wks.location}/ExampleApp/src/**.cpp",
        "%{wks.location}/ExampleApp/src/**.h",
    }