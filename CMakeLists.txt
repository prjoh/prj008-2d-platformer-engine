cmake_minimum_required(VERSION 3.24)
project(prj008)
set(EXECUTABLE_NAME "Game")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

##########################################################################################
# Project output directories for all builds (Debug, Release, etc.)
##########################################################################################

set(BUILD_DIR_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/Build/Debug)
set(BUILD_DIR_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/Build/Release)
set(BUILD_DIR_MINSIZEREL ${CMAKE_CURRENT_SOURCE_DIR}/Build/MinSizeRel)
set(BUILD_DIR_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/Build/RelWithDebInfo)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${BUILD_DIR_DEBUG}/Lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${BUILD_DIR_DEBUG}/Lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BUILD_DIR_DEBUG}/Bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${BUILD_DIR_RELEASE}/Lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${BUILD_DIR_RELEASE}/Lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BUILD_DIR_RELEASE}/Bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${BUILD_DIR_MINSIZEREL}/Lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${BUILD_DIR_MINSIZEREL}/Lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${BUILD_DIR_MINSIZEREL}/Bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${BUILD_DIR_RELWITHDEBINFO}/Lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${BUILD_DIR_RELWITHDEBINFO}/Lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${BUILD_DIR_RELWITHDEBINFO}/Bin)

##########################################################################################
# Add dependencies
##########################################################################################

set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ThirdParty)

# Add Raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
add_subdirectory(${THIRD_PARTY_DIR}/raylib-5.0 ${CMAKE_BINARY_DIR}/ThirdParty/raylib)

# Add Box2d
set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "" FORCE)
# TODO: This is a hack to allow compilation on MacOS
if (APPLE)
  set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
endif()
add_subdirectory(${THIRD_PARTY_DIR}/box2d-2.4.1 ${CMAKE_BINARY_DIR}/ThirdParty/box2d)

# Add fmt
add_subdirectory(${THIRD_PARTY_DIR}/fmt-10.2.1 ${CMAKE_BINARY_DIR}/ThirdParty/fmt)

# Add imgui
add_subdirectory(${THIRD_PARTY_DIR}/imgui-docking-1.90.5 ${CMAKE_BINARY_DIR}/ThirdParty/imgui-docking)

# Add rlImGui (imgui backend)
add_subdirectory(${THIRD_PARTY_DIR}/rlImGui ${CMAKE_BINARY_DIR}/ThirdParty/rlImGui)


##########################################################################################
# Project executable setup
##########################################################################################

# Adding our source files
set(PROJECT_SOURCES 
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Config.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Core/Application.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Core/Application.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Core/ApplicationCore.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Core/Colors.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Core/Colors.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Core/DebugInfo.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Core/DebugInfo.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Core/Error.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Core/Error.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Core/Guid.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Core/Guid.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Core/IRenderSurface.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Core/Log.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Core/Log.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Core/ObjectPool.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Core/RenderCore.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Core/Time.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Core/Time.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Core/Window.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ECS/Component.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ECS/ComponentFactory.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ECS/ComponentFactoryImpl.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ECS/ComponentFactoryImpl.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ECS/ComponentTupleContainer.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ECS/ComponentTypes.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ECS/Entity.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ECS/EntityManager.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ECS/EntityManager.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ECS/System.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ECS/Components/ColliderComponent.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ECS/Components/PlayerControllerComponent.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ECS/Components/SingletonCamera.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ECS/Components/SingletonInput.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ECS/Components/SingletonPlayerCommand.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ECS/Components/SingletonPhysicsContactInfo.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ECS/Components/SingletonPhysicsWorld.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ECS/Systems/ActorControllerSystem.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ECS/Systems/ActorControllerSystem.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ECS/Systems/CommandSystem.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ECS/Systems/CommandSystem.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ECS/Systems/PhysicsSystem.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ECS/Systems/PhysicsSystem.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ECS/Systems/RenderingSystem.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ECS/Systems/RenderingSystem.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Editor/Windows/EditorWindow.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Editor/Windows/GameViewWindow.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Editor/Windows/GameViewWindow.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Editor/Editor.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Editor/Editor.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Editor/EditorMainWindow.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Editor/EditorMainWindow.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/File/FileReader.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/File/FileWriter.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/File/Utils.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Game/Game.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Game/Game.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Game/GameMainWindow.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Game/GameMainWindow.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Game/MyStruct.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Game/MyStruct.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Game/Reflection.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Math/Util.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Math/Vector.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Math/Vector2.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Math/Vector4.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Memory/Memory.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Reflection/DefineTypeInfo.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Reflection/DefineTypeInfo.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Reflection/PropertyInfo.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Reflection/RegisterTypeInfo.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Reflection/RegisterTypeInfo.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Reflection/TypeId.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Reflection/TypeInfo.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Reflection/TypeInfo.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Reflection/TypeInfoData.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Reflection/TypeInfoDatabase.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Reflection/TypeInfoDatabase.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Reflection/TypeOffset.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Reflection/Utils.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Serialize/PrimitiveTypeSerializer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Serialize/PrimitiveTypeSerializer.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Serialize/StreamBuffer.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Serialize/StreamBufferRead.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Serialize/StreamBufferRead.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Serialize/StreamBufferReadWrite.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Serialize/StreamBufferReadWrite.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Serialize/Utils.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Util/BitFlag.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Util/Extension.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Util/Format.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Util/NonCopyable.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Util/NonMovable.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Util/PrimitiveTypes.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Util/PhysicsContactListener.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Util/PhysicsContactListener.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Util/Singleton.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Util/StringBuilder.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Util/StringHash.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Util/TextUtils.h
)

# Define PROJECT_INCLUDE to be the path to the include directory of the project
set(PROJECT_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/Sources)

# Declaring our executable
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${EXECUTABLE_NAME})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
# target_compile_options(${PROJECT_NAME} PUBLIC -fno-rtti)

# linking out libraries
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_link_libraries(${PROJECT_NAME} PRIVATE box2d)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE rlImGui)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
  target_link_libraries(${PROJECT_NAME} PRIVATE "-framework IOKit")
  target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Cocoa")
  target_link_libraries(${PROJECT_NAME} PRIVATE "-framework OpenGL")
endif()
