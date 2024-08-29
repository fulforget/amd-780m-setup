#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "roc::hipsparse" for configuration "Release"
set_property(TARGET roc::hipsparse APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(roc::hipsparse PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/libhipsparse.dll.a"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "roc::rocsparse"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/libhipsparse.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS roc::hipsparse )
list(APPEND _IMPORT_CHECK_FILES_FOR_roc::hipsparse "${_IMPORT_PREFIX}/lib/libhipsparse.dll.a" "${_IMPORT_PREFIX}/bin/libhipsparse.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
