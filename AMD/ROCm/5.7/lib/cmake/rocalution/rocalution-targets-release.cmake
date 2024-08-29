#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "roc::rocalution" for configuration "Release"
set_property(TARGET roc::rocalution APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(roc::rocalution PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/rocalution.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/rocalution.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS roc::rocalution )
list(APPEND _IMPORT_CHECK_FILES_FOR_roc::rocalution "${_IMPORT_PREFIX}/lib/rocalution.lib" "${_IMPORT_PREFIX}/bin/rocalution.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
