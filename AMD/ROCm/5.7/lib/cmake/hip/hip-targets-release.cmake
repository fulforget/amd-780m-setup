#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "hip::amdhip64" for configuration "Release"
set_property(TARGET hip::amdhip64 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hip::amdhip64 PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/amdhip64.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/amdhip64.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS hip::amdhip64 )
list(APPEND _IMPORT_CHECK_FILES_FOR_hip::amdhip64 "${_IMPORT_PREFIX}/lib/amdhip64.lib" "${_IMPORT_PREFIX}/bin/amdhip64.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
