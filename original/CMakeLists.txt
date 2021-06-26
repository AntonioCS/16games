project(16games_original CXX)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

# If you want SFML to provide an implementation of main():
# target_link_libraries(main PRIVATE sfml-main)

add_subdirectory("01 Tetris")