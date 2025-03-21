cmake_minimum_required(VERSION 3.17)

include(CTest)
enable_testing()

set(CMAKE_TESTDRIVER_BEFORE_TESTMAIN "grLog_useWindowsDebugOutput = false;")

create_test_sourcelist(
        tests
        gtlTests.cpp
        CommandLineParserTest.cpp
        EXTRA_INCLUDE "gtlUtil/Logging.h"
)

add_executable(gtlTests ${tests})
target_include_directories(gtlTests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

set(tests_to_run ${tests})
list(REMOVE_ITEM tests_to_run gtlTests.cpp)

target_link_libraries(gtlTests gtl gtlTestLib)

foreach(test ${tests_to_run})
    get_filename_component(test_name ${test} NAME_WE)
    add_test(NAME ${test_name} COMMAND gtlTests ${test_name})
endforeach()
