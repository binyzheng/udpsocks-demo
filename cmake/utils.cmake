#copy function
function(copyFiles)
file(GLOB_RECURSE copyPatternFiles ${ARGV1})
foreach(msg ${copyPatternFiles})
    add_custom_command(TARGET ${ARGV0}
					POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_if_different ${msg} $<TARGET_FILE_DIR:${ARGV0}>)
endforeach()
endfunction()