workspace "DCRend"
	configurations { "Debug", "Release" }

project "DCRend"
	kind "ConsoleApp"
	language "C++"
    architecture "x64"
	targetdir "bin/%{cfg.buildcfg}"

	includedirs { "lib/glfw/include" }
	libdirs { "lib/glfw/lib" }
	links { "glfw3", "opengl32" }
	files  { "src/*.h", "src/*.cpp" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		flags { "Symbols" }

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"