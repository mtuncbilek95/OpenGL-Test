cmake_minimum_required(VERSION 3.26)

# ---------------------- CMAKE INCLUDES ----------------------
include("${CMAKE_SOURCE_DIR}/Scripts/CMake/FetchLibraries.cmake")
# ------------------------------------------------------------

# ---------------------- CMAKE FETCH -------------------------
FetchContent_MakeAvailable(stbi)
FetchContent_MakeAvailable(glfw)
# ------------------------------------------------------------

# ---------------------- FILE ADDITION -----------------------
file(GLOB_RECURSE SUBDIRECTORIES "${CMAKE_SOURCE_DIR}/Source/OpenGLTest/*.cpp" "${CMAKE_SOURCE_DIR}/Source/OpenGLTest/*.h")
source_group(TREE "${CMAKE_SOURCE_DIR}/Source/OpenGLTest" FILES ${SUBDIRECTORIES})
add_executable(OpenGLTest main.cpp ${SUBDIRECTORIES})
# ------------------------------------------------------------

# ------------------- INCLUDE DIRECTORIES --------------------
target_include_directories(OpenGLTest PRIVATE "${CMAKE_SOURCE_DIR}/Source/MiniVk")
# ------------------------------------------------------------

# --------------------- LINK LIBRARIES -----------------------
target_link_libraries(OpenGLTest PUBLIC glfw)
# ------------------------------------------------------------

# ----------------- STB IMAGE IMPLEMENTATION -----------------
if (stbi_POPULATED) 
    target_compile_definitions(OpenGLTest PUBLIC STB_IMAGE_IMPLEMENTATION)
    target_compile_definitions(OpenGLTest PUBLIC STB_TRUETYPE_IMPLEMENTATION)

    target_include_directories(OpenGLTest PUBLIC ${stbi_SOURCE_DIR})
endif ()
# ------------------------------------------------------------

# -------------------- GLAD IMPLEMENTATION -------------------
FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
    FetchContent_Populate(glad)
    set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")
    set(GLAD_API "gl=" CACHE STRING "API type/version pairs, like \"gl=4.6,gles=\", no version means latest")
    set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for")
    add_subdirectory(${glad_SOURCE_DIR} ${glad_BINARY_DIR})
endif()
# ------------------------------------------------------------

# ----------------- PREPROCESSOR DEFINITIONS -----------------
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_definitions(OpenGLTest PUBLIC MINIGL_DEBUG)
endif ()

if (CMAKE_BUILD_TYPE STREQUAL Release)
    target_compile_definitions(OpenGLTest PUBLIC MINIGL_RELEASE)
endif ()
# ------------------------------------------------------------

# ------------------ PLATFORM DEFINITIONS --------------------
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_definitions(OpenGLTest PUBLIC MINIGL_PLATFORM_WINDOWS=1)
else()
	message(FATAL_ERROR "[CMAKE ERROR] -- UNSUPPORTED PLATFORM. PLEASE CHECK YOUR COMPILER AND PLATFORM.")
endif()
# ------------------------------------------------------------

# -------------------- MACRO DEFINITIONS ---------------------
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_definitions(OpenGLTest PUBLIC RUNTIME_API=__declspec\(dllexport\))
    target_compile_definitions(OpenGLTest PUBLIC FORCEINLINE=__forceinline)
    target_compile_definitions(OpenGLTest PUBLIC NOINLINE=__declspec\(noinline\))
    target_compile_definitions(OpenGLTest PUBLIC INLINE=__inline)
    target_compile_definitions(OpenGLTest PUBLIC NULLPTR=decltype\(nullptr\)\(\))
else()
	message(FATAL_ERROR "[CMAKE ERROR] -- UNSUPPORTED COMPILER. PLEASE CHECK YOUR COMPILER AND PLATFORM.")
endif()
# ------------------------------------------------------------