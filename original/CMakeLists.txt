project(16games_original CXX)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

# If you want SFML to provide an implementation of main():
# target_link_libraries(main PRIVATE sfml-main)

function(sfml_game targetName)
    add_executable(${targetName} WIN32
        ${ARGN}
    )

    target_link_libraries(${targetName} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
    target_link_libraries(${targetName} PRIVATE spdlog::spdlog spdlog::spdlog_header_only)

    #to remove console and still have function main as entrypoint
    if (WIN32)
        target_link_options(${targetName} PRIVATE "/ENTRY:mainCRTStartup")
    endif()

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
#add_subdirectory("04 Snake")
#add_subdirectory("05 Minesweeper")
#add_subdirectory("06 Fifteen-Puzzle")
#add_subdirectory("07 Racing (Top Down)")
#add_subdirectory("08 Outrun")
#add_subdirectory("09 Xonix")
#add_subdirectory("10 Bejeweled")
#add_subdirectory("11 NetWalk (Pipe Puzzle)")
#
