add library (vyuhaone_engine)

target_sources(vyuhaone_engine PRIVATE
    src/version.cpp
)

target_sources(vyuhaone_engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)