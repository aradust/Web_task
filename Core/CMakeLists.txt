add_library(Core SHARED src/core.cpp)
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
install(TARGETS Core LIBRARY DESTINATION /usr/local/lib)