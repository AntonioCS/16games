project(16games_original_tetris CXX)

add_executable(16games_original_tetris
#WIN32
	main.cpp
)



target_link_libraries(16games_original_tetris PRIVATE sfml-system sfml-network sfml-graphics sfml-window)


add_custom_command(
    TARGET 16games_original_tetris POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_PROPERTY:16games_original_tetris,SOURCE_DIR>/images
        $<TARGET_PROPERTY:16games_original_tetris,BINARY_DIR>/images
)
#target_link_options(16games_original_tetris PRIVATE "/ENTRY:mainCRTStartup")

#target_link_libraries(16games_original_tetris PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_image SDL2::SDL2_mixer SDL2::SDL2_ttf)
