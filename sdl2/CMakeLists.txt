project(16games_sdl2 CXX)

find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-ttf CONFIG REQUIRED)
find_package(sdl2-mixer CONFIG REQUIRED)
find_package(sdl2-net CONFIG REQUIRED)
find_package(sdl2-gfx CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

function(sdl2_game targetName)
    set(GEPartialPathPath "${CMAKE_SOURCE_DIR}/include")

    add_executable(${targetName} WIN32
        ${ARGN}
        "${GEPartialPathPath}/GameEngine/Game.cpp"
        "${GEPartialPathPath}/GameEngine/Texture.cpp"
        "${GEPartialPathPath}/GameEngine/Clock.cpp"
        "${GEPartialPathPath}/GameEngine/UsesRenderer.cpp"
        "${GEPartialPathPath}/GameEngine/Color.cpp"
        "${GEPartialPathPath}/GameEngine/ColorList.cpp"
    )

    target_include_directories(${targetName} PUBLIC ${GEPartialPathPath})

    target_link_libraries(${targetName} PRIVATE SDL2::SDL2 SDL2::SDL2main)
    target_link_libraries(${targetName} PRIVATE SDL2::SDL2_image)
    target_link_libraries(${targetName} PRIVATE SDL2::SDL2_ttf)
    target_link_libraries(${targetName} PRIVATE SDL2::SDL2_mixer)
    target_link_libraries(${targetName} PRIVATE SDL2::SDL2_net)
    target_link_libraries(${targetName} PRIVATE SDL2::SDL2_gfx)    
    target_link_libraries(${targetName} PRIVATE spdlog::spdlog spdlog::spdlog_header_only)    

    #to remove console and still have function main as entrypoint
    #if (WIN32)
    #    target_link_options(${targetName} PRIVATE "/ENTRY:mainCRTStartup")
    #endif()

    add_custom_command(
        TARGET ${targetName} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            $<TARGET_PROPERTY:${targetName},SOURCE_DIR>/resources
            $<TARGET_PROPERTY:${targetName},BINARY_DIR>/resources
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
