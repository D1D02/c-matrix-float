add_executable(example example.c)
target_link_libraries(example PRIVATE matrix)
set_property(TARGET example PROPERTY C_STANDARD 99)