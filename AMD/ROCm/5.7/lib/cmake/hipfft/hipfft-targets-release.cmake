#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "hip::hipfft" for configuration "Release"
set_property(TARGET hip::hipfft APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hip::hipfft PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/hipfft.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "roc::rocfft"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/hipfft.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS hip::hipfft )
list(APPEND _IMPORT_CHECK_FILES_FOR_hip::hipfft "${_IMPORT_PREFIX}/lib/hipfft.lib" "${_IMPORT_PREFIX}/bin/hipfft.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
