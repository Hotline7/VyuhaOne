add_library(vyuhaone_engine)

target_compile_features(vyuhaone_engine PUBLIC cxx_std_20)

#===============================================================================
# Source Files
#===============================================================================
target_sources(vyuhaone_engine
    PRIVATE
        src/version.cpp
)
#===============================================================================
# Include Directories 
#===============================================================================
target_include_directories(vyuhaone_engine
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
#===============================================================================
# Definitions
#===============================================================================
target_compile_definitions(vyuhaone_engine
    PRIVATE
        VYUHAONE_ENGINE_VERSION="${PROJECT_VERSION}"
)