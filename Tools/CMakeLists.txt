list(APPEND SOURCE tooltest)

find_package(fmt CONFIG REQUIRED)
find_package(clipp CONFIG REQUIRED)

foreach(src ${SOURCE})
    add_executable(${src} ${src}.cpp)
    target_link_libraries(${src} PRIVATE utils fmt::fmt clipp::clipp)
endforeach()
