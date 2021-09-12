project(vfs)
cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 14)
set(CXX_FLAGS "-Wall -g")

include_directories(impl/inc)

add_subdirectory(impl/src)
add_subdirectory(test)

find_package(Doxygen OPTIONAL_COMPONENTS dot)
if (DOXYGEN_FOUND)
  set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md")
  doxygen_add_docs(doc
    ${CMAKE_SOURCE_DIR}
  )
endif(DOXYGEN_FOUND)

add_custom_target(ALL COMMAND make run
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/impl/src
)
