#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "roc::rocblas" for configuration "Release"
set_property(TARGET roc::rocblas APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(roc::rocblas PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/rocblas.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/rocblas.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS roc::rocblas )
list(APPEND _IMPORT_CHECK_FILES_FOR_roc::rocblas "${_IMPORT_PREFIX}/lib/rocblas.lib" "${_IMPORT_PREFIX}/bin/rocblas.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)