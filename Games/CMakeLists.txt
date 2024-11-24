list(APPEND GAME_DIR Tetris)

foreach(dir ${GAME_DIR})
    add_subdirectory(${dir})
endforeach()
