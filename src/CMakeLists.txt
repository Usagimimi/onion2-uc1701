project(main)
cmake_minimum_required(VERSION 2.8)

add_executable(${PROJECT_NAME}
    gpio.c
    main.c
    uc1701.c
    ugpio.c
    ugpio-internal.c
    wrt-spi.c
    )

target_link_libraries(${PROJECT_NAME}
    )

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
