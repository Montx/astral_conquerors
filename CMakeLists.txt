cmake_minimum_required(VERSION 3.0)

project(astral_conquest VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)

set(OGRE_SDK_DIR "submodules/Ogre3D/build/sdk")
set(OGRE_DIR "${OGRE_SDK_DIR}/CMake")
set(OGRE_DLL_DIR "${OGRE_SDK_DIR}/bin")
set(OGRE_MEDIA_DIR "${OGRE_SDK_DIR}/media")

include_directories("submodules/imgui")

file(GLOB_RECURSE SOURCES 
    "source/*.cpp")
file(GLOB_RECURSE HEADERS 
    "source/*.h")

add_executable(astral_conquest ${SOURCES} ${HEADERS})

target_link_libraries(astral_conquest ${OGRE_LIBRARIES})

add_custom_command(
    TARGET astral_conquest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/${OGRE_DLL_DIR} $<TARGET_FILE_DIR:astral_conquest>
)
message("\n------ Created Ogre Bin Post-Build Copy Command ------")

add_custom_command(
    TARGET astral_conquest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/Media
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${OGRE_MEDIA_DIR} ${CMAKE_CURRENT_BINARY_DIR}/Media
)
message("\n------ Created Ogre Media Post-Build Copy Command ------")

message("\n------ Done ------\n")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT astral_conquest)


