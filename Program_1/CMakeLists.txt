add_executable(Program_1 src/main.cpp src/worker.cpp)
target_include_directories(Program_1 PRIVATE include)
target_link_libraries(Program_1 Core)