#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "roc::hipsolver" for configuration "Release"
set_property(TARGET roc::hipsolver APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(roc::hipsolver PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/hipsolver.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "roc::rocblas;roc::rocsolver"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/hipsolver.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS roc::hipsolver )
list(APPEND _IMPORT_CHECK_FILES_FOR_roc::hipsolver "${_IMPORT_PREFIX}/lib/hipsolver.lib" "${_IMPORT_PREFIX}/bin/hipsolver.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
