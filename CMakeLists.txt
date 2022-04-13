cmake_minimum_required(VERSION 3.20)

# ------------------ PROJECT ENTRY

project(KaraFunSocketIO VERSION 1.0.0)
if (MSVC)
    add_definitions(/MP)
endif()

# ------------------ OPTIONS

# ------------------ JSON SUB-TARGET

add_library(nlohmann_json INTERFACE)
add_library(nlohmann_json::nlohmann_json ALIAS nlohmann_json)
target_include_directories(nlohmann_json INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/lib/json)

# ------------------ SIOCLIENT SUBDIR

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/socket.io-client-cpp11-non-boost)

# ------------------ TARGET

set(KFSIO_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libkfsocketio/src)
file(GLOB KFSIO_SOURCES
    ${KFSIO_SOURCE_DIR}/*.cpp
    ${KFSIO_SOURCE_DIR}/*.h
)
add_library(KaraFunSocketIO SHARED ${KFSIO_SOURCES})
add_library(KaraFun::SocketIO ALIAS KaraFunSocketIO)
set_target_properties(KaraFunSocketIO PROPERTIES
    DEBUG_POSTFIX d
    FOLDER KaraFun
)
target_compile_features(KaraFunSocketIO PRIVATE cxx_std_17)

target_compile_definitions(KaraFunSocketIO
    PUBLIC
        DUNICODE
        _UNICODE
        KF_CALLCONV=__cdecl
        LIBKFSOCKETIO_EXPORTS
    PRIVATE
        _WEBSOCKETPP_CPP11_STL_
        _WEBSOCKETPP_CPP11_REGEX_
        _WEBSOCKETPP_NOEXCEPT_TOKEN_=noexcept
        ASIO_STANDALONE
        _USRDLL
)
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(KaraFunSocketIO PRIVATE -fdeclspec)
endif()
target_link_libraries(KaraFunSocketIO PRIVATE
    nlohmann_json::nlohmann_json
    sioclient_tls
)
target_include_directories(KaraFunSocketIO
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/KaraFunSocketIO>
    PRIVATE
        ${KFSIO_SOURCE_DIR}
)

# ----------------------- INSTALL

# Install target(s)
install(TARGETS KaraFunSocketIO EXPORT KaraFunSocketIOTargets)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include
    DESTINATION include/KaraFunSocketIO
    FILES_MATCHING PATTERN "*.h"
)
install(EXPORT KaraFunSocketIOTargets
    DESTINATION lib/KaraFunSocketIO/cmake
    NAMESPACE KaraFun::)

# Prepare install configuration
include(CMakePackageConfigHelpers)
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/KaraFunSocketIOConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/KaraFunSocketIOConfig.cmake
        @ONLY)
write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/KaraFunSocketIOConfigVersion.cmake
	COMPATIBILITY SameMinorVersion
)
install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/KaraFunSocketIOConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/KaraFunSocketIOConfigVersion.cmake
    DESTINATION
        lib/KaraFunSocketIO/cmake)