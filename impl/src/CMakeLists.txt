include_directories(${vfs_SOURCE_DIR}/impl/inc)
add_library(commands commands.cpp)
add_library(virtualFileSystem vfs.cpp)

add_executable(vfs main.cpp commands.cpp vfs.cpp)

target_link_libraries(vfs commands virtualFileSystem)
