workspace "DCRend"
	configurations { "Debug", "Release" }

project "DCRend"
	kind "ConsoleApp"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"

	files  { "src/*.h", "src/*.cpp" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		flags { "Symbols" }

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"