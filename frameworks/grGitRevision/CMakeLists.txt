cmake_minimum_required(VERSION 3.17)

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/include/grGitRevision")

find_package(Git)

add_library(grGitRevision OBJECT IMPORTED GLOBAL)

if (Git_FOUND)
    add_custom_target(grGitRevision_generate
            COMMENT "Generating Git revision header..."
            COMMAND ${CMAKE_COMMAND}
            -D GIT_EXECUTABLE=${GIT_EXECUTABLE}
            -D INPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/grGitRevision/Revision.h.in
            -D OUTPUT_FILE=${CMAKE_CURRENT_BINARY_DIR}/include/grGitRevision/Revision.h
            -P ${CMAKE_CURRENT_SOURCE_DIR}/gen_revision.cmake
            BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/include/grGitRevision/Revision.h
            )
    add_dependencies(grGitRevision grGitRevision_generate)
else ()
    set(GR_GIT_REVISION "unknown")
    configure_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/grGitRevision/Revision.h.in
            ${CMAKE_CURRENT_BINARY_DIR}/include/grGitRevision/Revision.h)
endif ()

target_include_directories(grGitRevision INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/include/)
