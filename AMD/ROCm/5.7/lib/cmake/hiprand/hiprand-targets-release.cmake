#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "hip::hiprand" for configuration "Release"
set_property(TARGET hip::hiprand APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hip::hiprand PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/hiprand.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "roc::rocrand"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/hiprand.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS hip::hiprand )
list(APPEND _IMPORT_CHECK_FILES_FOR_hip::hiprand "${_IMPORT_PREFIX}/lib/hiprand.lib" "${_IMPORT_PREFIX}/bin/hiprand.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
