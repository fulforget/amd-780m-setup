#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "roc::rocfft" for configuration "Release"
set_property(TARGET roc::rocfft APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(roc::rocfft PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/rocfft.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/rocfft.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS roc::rocfft )
list(APPEND _IMPORT_CHECK_FILES_FOR_roc::rocfft "${_IMPORT_PREFIX}/lib/rocfft.lib" "${_IMPORT_PREFIX}/bin/rocfft.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
