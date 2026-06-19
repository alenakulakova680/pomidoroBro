cmake_minimum_required(VERSION 3.24)
project(PomodoroBro VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(NOT DEFINED SFML_ROOT)
    set(SFML_ROOT "C:/SFML")
endif()

add_executable(pomodoro_bro
    src/main.cpp
    src/Button.cpp
    src/TimerLogic.cpp
)

target_include_directories(pomodoro_bro PRIVATE 
    include
    ${SFML_INCLUDE_DIR}
)

target_link_libraries(pomodoro_bro PRIVATE 
    sfml-graphics 
    sfml-window 
    sfml-audio 
    sfml-system
)

add_custom_command(
    TARGET pomodoro_bro POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:pomodoro_bro>/assets"
)

enable_testing()

add_executable(runTests 
    src/tests.cpp 
    src/TimerLogic.cpp 
    src/Button.cpp
)

target_include_directories(runTests PRIVATE 
    include
    ${SFML_INCLUDE_DIR}
)

target_link_libraries(runTests PRIVATE 
    sfml-graphics 
    sfml-window 
    sfml-audio 
    sfml-system
)

add_test(NAME PomodoroTests COMMAND runTests)