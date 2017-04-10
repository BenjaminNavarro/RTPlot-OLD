# Apps
include_directories(${RTPLOT_INCLUDE_DIRS})

function(add_application app)
    file(GLOB_RECURSE app_source_files ${CMAKE_CURRENT_SOURCE_DIR}/${app}/*)
    add_executable(${app} ${app_source_files})
    set_property(TARGET ${app} PROPERTY CXX_STANDARD 14)
    target_link_libraries(${app} rtplot-lib)
endfunction()

add_application(rtplot)
add_application(test_rtplot)
