add_library(matrix STATIC matrix.c)
target_include_directories(matrix PUBLIC ../include)
set_property(TARGET matrix PROPERTY C_STANDARD 99)