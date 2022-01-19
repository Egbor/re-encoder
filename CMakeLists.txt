cmake_minimum_required(VERSION 3.7.2)

project(ffutil)

function(find_libraries OUT_ARGUMENT)
  set(RESULT)
  foreach(LIBRARY_NAME_ELEMENT ${ARGN})
    find_library(FULL_LIBRARY_PATH ${LIBRARY_NAME_ELEMENT})
    if(${FULL_LIBRARY_PATH} STREQUAL "FULL_LIBRARY_PATH-NOTFOUND")
      message(WARNING "${LIBRARY_NAME_ELEMENT} not found")
    endif()
    list(APPEND RESULT ${FULL_LIBRARY_PATH})
    unset(FULL_LIBRARY_PATH CACHE) # without this line find_library() will return the same data
  endforeach()
  set(${OUT_ARGUMENT} ${RESULT} PARENT_SCOPE)
endfunction()

set(SOURCE_DIR "src/")

set(FFMPEG_ROOT_DIR "x86_64-linux-gnu/")
set(FFMPEG_DEPENDENCIES avformat avcodec avutil swscale swresample m pthread)

include_directories("/usr/include/${FFMPEG_ROOT_DIR}")
link_directories("/usr/lib/${FFMPEG_ROOT_DIR}")

file(GLOB_RECURSE SOURCES "${SOURCE_DIR}*.c")
find_libraries(FFMPEG_LIBRARIES ${FFMPEG_DEPENDENCIES})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${FFMPEG_LIBRARIES})

#message(STATUS "FFMPEG_LIBRARIES=${FFMPEG_LIBRARIES}")
