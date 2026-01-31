cmake_minimum_required (VERSION 3.0)
project (testapp)

# Require MPI for this project:
find_package(MPI REQUIRED)

add_executable(testapp testapp.c)

set_target_properties(testapp PROPERTIES INCLUDE_DIRECTORIES "${MPI_C_INCLUDE_PATH}")
set_target_properties(testapp PROPERTIES COMPILE_FLAGS "${MPI_C_COMPILE_FLAGS}")
set_target_properties(testapp PROPERTIES LINK_FLAGS "${MPI_C_LINK_FLAGS}")
target_link_libraries(testapp PRIVATE "${MPI_C_LIBRARIES}")

# A custom command, distclean, to remove files that are created
add_custom_target(distclean COMMAND rm -rf CMakeCache.txt CMakeFiles
                  CTestTestfile.cmake Makefile Testing cmake_install.cmake)
