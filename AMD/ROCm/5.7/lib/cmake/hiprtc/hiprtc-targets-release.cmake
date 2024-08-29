#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "hiprtc::hiprtc" for configuration "Release"
set_property(TARGET hiprtc::hiprtc APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hiprtc::hiprtc PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/hiprtc.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/hiprtc0507.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS hiprtc::hiprtc )
list(APPEND _IMPORT_CHECK_FILES_FOR_hiprtc::hiprtc "${_IMPORT_PREFIX}/lib/hiprtc.lib" "${_IMPORT_PREFIX}/bin/hiprtc0507.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
