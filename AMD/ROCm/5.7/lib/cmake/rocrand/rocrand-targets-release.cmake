#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "roc::rocrand" for configuration "Release"
set_property(TARGET roc::rocrand APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(roc::rocrand PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/rocrand.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/rocrand.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS roc::rocrand )
list(APPEND _IMPORT_CHECK_FILES_FOR_roc::rocrand "${_IMPORT_PREFIX}/lib/rocrand.lib" "${_IMPORT_PREFIX}/bin/rocrand.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
