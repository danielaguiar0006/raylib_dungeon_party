cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(dungeon_party)
set(CMAKE_BUILD_TYPE Debug)

# Set the C Standard to C17
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)
#set(raylib_DIR "C:/dev/libraries/raylib/cmake/")
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED

#Uncomment this if you want to download raylib automatically and remove raylib_DIR
  if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()


# Our Project
set(SOURCE_FILES src/main.c  src/utils/globals.c src/utils/grid.c src/core/logger.c src/entities/entity.c src/components/tag_component.c src/components/transform_component.c src/components/component_manager.c
    src/systems/draw_sprites.c src/systems/update_entity_transforms.c src/systems/inputs.c)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)

# Set output directories for different built types
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release
    # RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_SOURCE_DIR}/bin/RelWithDebInfo
    # RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_SOURCE_DIR}/bin/MinSizeRel
)

# Web Configurations
#[[
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()
]]

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
