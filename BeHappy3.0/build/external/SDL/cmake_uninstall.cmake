if (NOT EXISTS "C:/Users/Rocket/source/repos/BeHappy3.0/BeHappy3.0/build/install_manifest.txt")
    message(FATAL_ERROR "Cannot find install manifest: \"C:/Users/Rocket/source/repos/BeHappy3.0/BeHappy3.0/build/install_manifest.txt\"")
endif()

file(READ "C:/Users/Rocket/source/repos/BeHappy3.0/BeHappy3.0/build/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach(file ${files})
    message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
    execute_process(
        COMMAND C:/Program Files/CMake/bin/cmake.exe -E remove "$ENV{DESTDIR}${file}"
        OUTPUT_VARIABLE rm_out
        RESULT_VARIABLE rm_retval
    )
    if(NOT ${rm_retval} EQUAL 0)
        message(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif (NOT ${rm_retval} EQUAL 0)
endforeach()
