string(REGEX MATCH "^[0-9]*" ICU_VERSION_MAJOR "${VERSION}")
string(REPLACE "." "_" VERSION2 "${VERSION}")
string(REPLACE "." "-" VERSION3 "${VERSION}")

vcpkg_download_distfile(
    ARCHIVE
    URLS "https://github.com/unicode-org/icu/releases/download/release-${VERSION3}/icu4c-${VERSION2}-src.tgz"
    FILENAME "icu4c-${VERSION2}-src.tgz"
    SHA512 e788e372716eecebc39b56bbc88f3a458e21c3ef20631c2a3d7ef05794a678fe8dad482a03a40fdb9717109a613978c7146682e98ee16fade5668d641d5c48f8
)

vcpkg_extract_source_archive(SOURCE_PATH
    ARCHIVE "${ARCHIVE}"
    PATCHES
        disable-escapestr-tool.patch
        # remove-MD-from-configure.patch
        fix-extra.patch
        mingw-dll-install.patch
        disable-static-prefix.patch # https://gitlab.kitware.com/cmake/cmake/-/issues/16617; also mingw.
        fix-win-build.patch
        vcpkg-cross-data.patch
)

# download data sources
vcpkg_download_distfile(
        DATA_ARCHIVE
        URLS "https://github.com/unicode-org/icu/releases/download/release-${VERSION3}/icu4c-${VERSION2}-data.zip"
        FILENAME "icu4c-${VERSION2}-data.zip"
        SHA512 9772b9d9ea5e3def2309044d41ea9b18f34a3448c1e5ed6ad985f517dd41ee697e08bccfa702b706a18d9c91100a80a958b846bd181b8d1ca78fdebf7447ba78
)

vcpkg_extract_source_archive(DATA_SOURCE_PATH
    ARCHIVE "${DATA_ARCHIVE}"
    PATCHES
        fix_parallel_build_on_windows.patch
)


file(REMOVE_RECURSE "${SOURCE_PATH}/source/data")
file(RENAME "${DATA_SOURCE_PATH}" "${SOURCE_PATH}/source/data")

vcpkg_find_acquire_program(PYTHON3)
set(ENV{PYTHON} "${PYTHON3}")
set(ENV{ICU_DATA_FILTER_FILE} "${CMAKE_CURRENT_LIST_DIR}/filters.json")

vcpkg_list(SET CONFIGURE_OPTIONS)
vcpkg_list(SET CONFIGURE_OPTIONS_RELEASE)
vcpkg_list(SET CONFIGURE_OPTIONS_DEBUG)
vcpkg_list(SET BUILD_OPTIONS)

if(VCPKG_TARGET_IS_EMSCRIPTEN)
    vcpkg_list(APPEND CONFIGURE_OPTIONS --disable-extras)
    vcpkg_list(APPEND BUILD_OPTIONS "PKGDATA_OPTS=--without-assembly -O ../data/icupkg.inc")
endif()

if(VCPKG_TARGET_IS_WINDOWS)
    list(APPEND CONFIGURE_OPTIONS --enable-icu-build-win)
endif()

list(APPEND CONFIGURE_OPTIONS --disable-samples --disable-tests --disable-layoutex)

list(APPEND CONFIGURE_OPTIONS_RELEASE --disable-debug --enable-release)
list(APPEND CONFIGURE_OPTIONS_DEBUG  --enable-debug --disable-release)

set(CONFIG_TRIPLETS)
list(APPEND CONFIG_TRIPLETS ${TARGET_TRIPLET}-rel)
if (NOT DEFINED VCPKG_BUILD_TYPE OR VCPKG_BUILD_TYPE STREQUAL "debug")
  list(APPEND CONFIG_TRIPLETS ${TARGET_TRIPLET}-dbg)
endif()

if("tools" IN_LIST FEATURES)
  list(APPEND CONFIGURE_OPTIONS --enable-tools)
else()
  list(APPEND CONFIGURE_OPTIONS --disable-tools)
endif()
if(CMAKE_HOST_WIN32 AND VCPKG_TARGET_IS_MINGW AND NOT HOST_TRIPLET MATCHES "mingw")
    # Assuming no cross compiling because the host (windows) pkgdata tool doesn't
    # use the '/' path separator when creating compiler commands for mingw bash.
elseif(VCPKG_CROSSCOMPILING)
    set(TOOL_PATH "${CURRENT_HOST_INSTALLED_DIR}/tools/${PORT}")
    # convert to unix path
    string(REGEX REPLACE "^([a-zA-Z]):/" "/\\1/" _VCPKG_TOOL_PATH "${TOOL_PATH}")
    list(APPEND CONFIGURE_OPTIONS "--with-cross-build=${_VCPKG_TOOL_PATH}")
endif()

vcpkg_configure_make(
    SOURCE_PATH "${SOURCE_PATH}"
    AUTOCONFIG
    PROJECT_SUBPATH source
    ADDITIONAL_MSYS_PACKAGES autoconf-archive
    OPTIONS ${CONFIGURE_OPTIONS}
    OPTIONS_RELEASE ${CONFIGURE_OPTIONS_RELEASE}
    OPTIONS_DEBUG ${CONFIGURE_OPTIONS_DEBUG}
    DETERMINE_BUILD_TRIPLET
)

if(VCPKG_TARGET_IS_OSX AND VCPKG_LIBRARY_LINKAGE STREQUAL "dynamic")

    vcpkg_build_make()
    # remove this block if https://unicode-org.atlassian.net/browse/ICU-21458
    # is resolved and use the configure script instead
    if(DEFINED CMAKE_INSTALL_NAME_DIR)
        set(ID_PREFIX "${CMAKE_INSTALL_NAME_DIR}")
    else()
        set(ID_PREFIX "@rpath")
    endif()

    # install_name_tool may be missing if cross-compiling
    find_program(
        INSTALL_NAME_TOOL
        install_name_tool
        HINTS /usr/bin /Library/Developer/CommandLineTools/usr/bin/
        DOC "Absolute path of install_name_tool"
        REQUIRED
    )

    message(STATUS "setting rpath prefix for macOS dynamic libraries")

    if("tools" IN_LIST FEATURES)
        set(LIBICUTU_RPATH "libicutu")
    endif()

    #31680: Fix @rpath in both debug and release build
    foreach(CONFIG_TRIPLE IN LISTS CONFIG_TRIPLETS)
        # add ID_PREFIX to libicudata libicui18n libicuio libicutu libicuuc
        foreach(LIB_NAME IN ITEMS libicudata libicui18n libicuio ${LIBICUTU_RPATH} libicuuc)
            vcpkg_execute_build_process(
                COMMAND "${INSTALL_NAME_TOOL}" -id "${ID_PREFIX}/${LIB_NAME}.${ICU_VERSION_MAJOR}.dylib"
                "${LIB_NAME}.${VERSION}.dylib"
                WORKING_DIRECTORY "${CURRENT_BUILDTREES_DIR}/${CONFIG_TRIPLE}/lib"
                LOGNAME "make-build-fix-rpath-${CONFIG_TRIPLE}"
            )
        endforeach()

        # add ID_PREFIX to libicui18n libicuio libicutu dependencies
        foreach(LIB_NAME IN ITEMS libicui18n libicuio)
            vcpkg_execute_build_process(
                COMMAND "${INSTALL_NAME_TOOL}" -change "libicuuc.${ICU_VERSION_MAJOR}.dylib"
                                                    "${ID_PREFIX}/libicuuc.${ICU_VERSION_MAJOR}.dylib"
                                                    "${LIB_NAME}.${VERSION}.dylib"
                WORKING_DIRECTORY "${CURRENT_BUILDTREES_DIR}/${CONFIG_TRIPLE}/lib"
                LOGNAME "make-build-fix-rpath-${CONFIG_TRIPLE}"
            )
            vcpkg_execute_build_process(
                COMMAND "${INSTALL_NAME_TOOL}" -change "libicudata.${ICU_VERSION_MAJOR}.dylib"
                                                    "${ID_PREFIX}/libicudata.${ICU_VERSION_MAJOR}.dylib"
                                                    "${LIB_NAME}.${VERSION}.dylib"
                WORKING_DIRECTORY "${CURRENT_BUILDTREES_DIR}/${CONFIG_TRIPLE}/lib"
                LOGNAME "make-build-fix-rpath-${CONFIG_TRIPLE}"
            )
        endforeach()

        # add ID_PREFIX to remaining libicuio libicutu dependencies
        foreach(LIB_NAME libicuio libicutu)
            vcpkg_execute_build_process(
                COMMAND "${INSTALL_NAME_TOOL}" -change "libicui18n.${ICU_VERSION_MAJOR}.dylib"
                                                    "${ID_PREFIX}/libicui18n.${ICU_VERSION_MAJOR}.dylib"
                                                    "${LIB_NAME}.${VERSION}.dylib"
                WORKING_DIRECTORY "${CURRENT_BUILDTREES_DIR}/${CONFIG_TRIPLE}/lib"
                LOGNAME "make-build-fix-rpath-${CONFIG_TRIPLE}"
            )
        endforeach()

        # add ID_PREFIX to libicuuc dependencies
        vcpkg_execute_build_process(
            COMMAND "${INSTALL_NAME_TOOL}" -change "libicudata.${ICU_VERSION_MAJOR}.dylib"
                                                "${ID_PREFIX}/libicudata.${ICU_VERSION_MAJOR}.dylib"
                                                "libicuuc.${VERSION}.dylib"
            WORKING_DIRECTORY "${CURRENT_BUILDTREES_DIR}/${CONFIG_TRIPLE}/lib"
            LOGNAME "make-build-fix-rpath-${CONFIG_TRIPLE}"
        )
    endforeach()

endif()

vcpkg_install_make(OPTIONS ${BUILD_OPTIONS})

file(REMOVE_RECURSE
    "${CURRENT_PACKAGES_DIR}/share"
    "${CURRENT_PACKAGES_DIR}/debug/share"
    "${CURRENT_PACKAGES_DIR}/lib/icu"
    "${CURRENT_PACKAGES_DIR}/debug/lib/icu"
    "${CURRENT_PACKAGES_DIR}/debug/lib/icud")

file(GLOB TEST_LIBS
    "${CURRENT_PACKAGES_DIR}/lib/*test*"
    "${CURRENT_PACKAGES_DIR}/debug/lib/*test*")
if(TEST_LIBS)
    file(REMOVE ${TEST_LIBS})
endif()

if(VCPKG_LIBRARY_LINKAGE STREQUAL "static")
    # force U_STATIC_IMPLEMENTATION macro
    foreach(HEADER utypes.h utf_old.h platform.h)
        vcpkg_replace_string("${CURRENT_PACKAGES_DIR}/include/unicode/${HEADER}" "defined(U_STATIC_IMPLEMENTATION)" "1")
    endforeach()
endif()

# Install executables from /tools/icu/sbin to /tools/icu/bin on unix (/bin because icu require this for cross compiling)
if(VCPKG_TARGET_IS_LINUX OR VCPKG_TARGET_IS_OSX AND "tools" IN_LIST FEATURES)
    vcpkg_copy_tools(
        TOOL_NAMES icupkg gennorm2 gencmn genccode gensprep
        SEARCH_DIR "${CURRENT_PACKAGES_DIR}/tools/${PORT}/sbin"
        DESTINATION "${CURRENT_PACKAGES_DIR}/tools/${PORT}/bin"
    )
endif()

file(REMOVE_RECURSE
    "${CURRENT_PACKAGES_DIR}/tools/${PORT}/sbin"
    "${CURRENT_PACKAGES_DIR}/tools/${PORT}/debug")

# To cross compile, we need some files at specific positions. So lets copy them
file(GLOB CROSS_COMPILE_DEFS "${CURRENT_BUILDTREES_DIR}/${TARGET_TRIPLET}-rel/config/icucross.*")
file(INSTALL ${CROSS_COMPILE_DEFS} DESTINATION "${CURRENT_PACKAGES_DIR}/tools/${PORT}/config")

file(GLOB RELEASE_DLLS "${CURRENT_PACKAGES_DIR}/lib/*icu*${ICU_VERSION_MAJOR}.dll")
file(COPY ${RELEASE_DLLS} DESTINATION "${CURRENT_PACKAGES_DIR}/tools/${PORT}/bin")

# copy dlls
file(GLOB RELEASE_DLLS "${CURRENT_PACKAGES_DIR}/lib/*icu*${ICU_VERSION_MAJOR}.dll")
file(COPY ${RELEASE_DLLS} DESTINATION "${CURRENT_PACKAGES_DIR}/bin")
if(NOT VCPKG_BUILD_TYPE)
    file(GLOB DEBUG_DLLS "${CURRENT_PACKAGES_DIR}/debug/lib/*icu*${ICU_VERSION_MAJOR}.dll")
    file(COPY ${DEBUG_DLLS} DESTINATION "${CURRENT_PACKAGES_DIR}/debug/bin")
endif()

# remove any remaining dlls in /lib
file(GLOB DUMMY_DLLS "${CURRENT_PACKAGES_DIR}/lib/*.dll" "${CURRENT_PACKAGES_DIR}/debug/lib/*.dll")
if(DUMMY_DLLS)
    file(REMOVE ${DUMMY_DLLS})
endif()

vcpkg_copy_pdbs()
vcpkg_fixup_pkgconfig()

vcpkg_replace_string("${CURRENT_PACKAGES_DIR}/tools/${PORT}/bin/icu-config" "${CURRENT_INSTALLED_DIR}" "`dirname $0`/../../../")

file(INSTALL "${CMAKE_CURRENT_LIST_DIR}/vcpkg-cmake-wrapper.cmake" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}")
vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/LICENSE")
