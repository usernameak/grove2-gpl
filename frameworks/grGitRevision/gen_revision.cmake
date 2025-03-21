cmake_minimum_required(VERSION 3.17)

# Git executable is extracted from parameters.
execute_process(COMMAND ${GIT_EXECUTABLE} describe --tags --always
        OUTPUT_VARIABLE GR_GIT_REVISION OUTPUT_STRIP_TRAILING_WHITESPACE RESULT_VARIABLE GIT_DESCRIBE_RESULT)

if (GIT_DESCRIBE_RESULT AND NOT GIT_DESCRIBE_RESULT EQUAL 0)
    set(GR_GIT_REVISION "unknown")
endif()

# Input and output files are extracted from parameters.
configure_file(${INPUT_FILE} ${OUTPUT_FILE})
