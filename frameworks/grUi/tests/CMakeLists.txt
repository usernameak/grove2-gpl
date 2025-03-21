cmake_minimum_required(VERSION 3.17)

include(CTest)

set(CMAKE_TESTDRIVER_BEFORE_TESTMAIN "grLog_useWindowsDebugOutput = false;")

create_test_sourcelist(
        tests
        grUiTests.cpp
        GSSTest.cpp
        EXTRA_INCLUDE "gtlUtil/Logging.h"
)

add_executable(grUiTests ${tests})
target_include_directories(grUiTests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(grUiTests grUi gtlTestLib)

add_test(NAME GSSTest COMMAND grUiTests GSSTest)
