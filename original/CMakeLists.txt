project(16games_original CXX)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

# If you want SFML to provide an implementation of main():
# target_link_libraries(main PRIVATE sfml-main)

function(sfml_game targetName)
    add_executable(${targetName}
    #WIN32
        ${ARGN}
    )

    target_link_libraries(${targetName} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

    add_custom_command(
        TARGET ${targetName} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            $<TARGET_PROPERTY:${targetName},SOURCE_DIR>/images
            $<TARGET_PROPERTY:${targetName},BINARY_DIR>/images
    )
endfunction()

add_subdirectory("01 Tetris")
add_subdirectory("02 Doodle Jump")
add_subdirectory("03 Arkanoid")
add_subdirectory("04 Snake")
add_subdirectory("05 Minesweeper")
add_subdirectory("06 Fifteen-Puzzle")
