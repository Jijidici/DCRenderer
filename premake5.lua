workspace "DCRend"
	configurations { "Debug", "Release" }

project "DCRend"
	kind "ConsoleApp"
	language "C++"
    architecture "x64"
	targetdir "bin/%{cfg.buildcfg}"

	prebuildcommands { "copy lib\\glfw\\bin\\glfw3.dll bin\\%{cfg.buildcfg}\\glfw3.dll ", 
					   "copy  lib\\glew\\bin\\Release\\x64\\glew32.dll bin\\%{cfg.buildcfg}\\glew32.dll"}

	includedirs { "lib/glfw/include", "lib/glew/include" }
	libdirs { "lib/glfw/lib", "lib/glew/lib/Release/x64" }
	links { "glfw3dll", "opengl32", "glew32" }
	files  { "src/*.h", "src/*.cpp", 
			 "src/display/*.h", "src/display/*.cpp" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		flags { "Symbols" }

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
	                    