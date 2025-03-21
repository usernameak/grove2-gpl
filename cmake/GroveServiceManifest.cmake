function(gbuild_CreateServiceManifest _target _services)
    list(TRANSFORM _services PREPEND "providesService: ")
    list(JOIN _services "\n" _services_str)
    set(_services_tmp_file "${CMAKE_CURRENT_BINARY_DIR}/services_target_${_target}.txt")
    file(WRITE "${_services_tmp_file}" "${_services_str}")
    add_custom_command(
            TARGET ${_target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${_services_tmp_file}" "$<TARGET_FILE:${_target}>.svc")
endfunction()