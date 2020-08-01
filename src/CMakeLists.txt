add_executable(main.out main.cpp)

target_include_directories(main.out
  PRIVATE ${PROJECT_SOURCE_DIR}/include/
)

target_link_libraries(main.out PUBLIC SDL2 GL SDL2_ttf)

