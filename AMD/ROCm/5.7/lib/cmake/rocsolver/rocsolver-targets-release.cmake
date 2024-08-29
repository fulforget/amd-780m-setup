#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "roc::rocsolver" for configuration "Release"
set_property(TARGET roc::rocsolver APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(roc::rocsolver PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/rocsolver.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "roc::rocsparse"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/rocsolver.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS roc::rocsolver )
list(APPEND _IMPORT_CHECK_FILES_FOR_roc::rocsolver "${_IMPORT_PREFIX}/lib/rocsolver.lib" "${_IMPORT_PREFIX}/bin/rocsolver.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
