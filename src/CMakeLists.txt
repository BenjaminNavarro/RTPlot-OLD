find_package(FLTK REQUIRED)
find_package(OpenGL REQUIRED)

###					RSCL library					###
set(RTPLOT_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include" CACHE INTERNAL "")
include_directories(${RTPLOT_INCLUDE_DIRS})
file(
    GLOB_RECURSE
    rtplot_source_files
    ${CMAKE_CURRENT_SOURCE_DIR}/rtplot/*
)

add_library(rtplot-lib SHARED ${rtplot_source_files})
target_link_libraries(rtplot-lib ${FLTK_LIBRARIES})
target_link_libraries(rtplot-lib ${OPENGL_LIBRARIES})
target_compile_definitions(rtplot-lib PRIVATE _LARGEFILE_SOURCE _LARGEFILE64_SOURCE _THREAD_SAFE _REENTRANT)
set_property(TARGET rtplot-lib PROPERTY CXX_STANDARD 11)
