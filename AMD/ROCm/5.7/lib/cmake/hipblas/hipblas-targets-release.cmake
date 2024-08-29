#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "roc::hipblas" for configuration "Release"
set_property(TARGET roc::hipblas APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(roc::hipblas PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/hipblas.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "roc::rocblas"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/hipblas.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS roc::hipblas )
list(APPEND _IMPORT_CHECK_FILES_FOR_roc::hipblas "${_IMPORT_PREFIX}/lib/hipblas.lib" "${_IMPORT_PREFIX}/bin/hipblas.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
