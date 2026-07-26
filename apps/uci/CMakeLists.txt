add_executable(vyuhaone_uci
    main.cpp
)

target_link_libraries(vyuhaone_uci
    PRIVATE
        vyuhaone_engine
)