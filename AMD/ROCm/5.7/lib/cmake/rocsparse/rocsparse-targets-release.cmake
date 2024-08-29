#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "roc::rocsparse" for configuration "Release"
set_property(TARGET roc::rocsparse APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(roc::rocsparse PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/rocsparse.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/rocsparse.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS roc::rocsparse )
list(APPEND _IMPORT_CHECK_FILES_FOR_roc::rocsparse "${_IMPORT_PREFIX}/lib/rocsparse.lib" "${_IMPORT_PREFIX}/bin/rocsparse.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
