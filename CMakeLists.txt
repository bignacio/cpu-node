cmake_minimum_required(VERSION 3.21)

project(cpu-nodes VERSION 1.0)


# Find kernel release and set it as include path
execute_process(
    COMMAND uname -r
    OUTPUT_VARIABLE KERNEL_RELEASE
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

include_directories(/usr/src/linux-headers-${KERNEL_RELEASE}/include )

add_executable(cpu-nodes cpu-nodes.c)

target_compile_options(cpu-nodes PRIVATE
    -Wall
    -Wpedantic
    -Werror
    -Wextra
    -Wconversion
    -Wsign-conversion
    -Walloca
    -Wshadow
    -Wfloat-equal
    -Wswitch-enum
    -Wcast-qual
    -Wimplicit-fallthrough
)
