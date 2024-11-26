project(Tetris)

file(GLOB_RECURSE SOURCES "*.cpp" "*.h")

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_definitions(utils PRIVATE _UNICODE UNICODE)

find_package(fmt CONFIG REQUIRED)
find_package(raylib CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt raylib)