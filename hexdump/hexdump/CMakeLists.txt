# CMakeList.txt : CMake project for hexdump, include source and define
# project specific logic here.
#

# Add source to this project's executable.
set(SRCS 
    "hexdump.c"
    "dynarray.c"
)
add_executable (hexdump ${SRCS})
set_target_properties(hexdump PROPERTIES 
    C_STANDARD 99
    C_EXTENSIONS OFF
)

 if (NOT ${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_executable (hexdump_address ${SRCS})
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        target_compile_options(hexdump_address PRIVATE
            "-fsanitize=address" "-g"
        )
        target_link_options(hexdump_address PRIVATE "clang_rt.asan-x86_64")
        target_link_directories(hexdump_address PRIVATE "C:\\Program Files\\LLVM\\lib\\windows")
    else()
        target_compile_options(hexdump_address PRIVATE
            "/fsanitize=address" "/Zi"
        )
    endif()
    set_target_properties(hexdump_address PROPERTIES 
        C_STANDARD 99
        C_EXTENSIONS OFF
    )
endif()
file(COPY test/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# TODO: Add tests and install targets if needed.
