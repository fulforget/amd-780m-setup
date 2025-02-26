# Copyright (C) 2021 Kitware, Inc. All Rights Reserved.
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was hip-lang-config.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################
include(CMakeFindDependencyMacro OPTIONAL RESULT_VARIABLE _CMakeFindDependencyMacro_FOUND)
if (NOT _CMakeFindDependencyMacro_FOUND)
  macro(find_dependency dep)
    if (NOT ${dep}_FOUND)
      set(cmake_fd_version)
      if (${ARGC} GREATER 1)
        set(cmake_fd_version ${ARGV1})
      endif()
      set(cmake_fd_exact_arg)
      if(${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION_EXACT)
        set(cmake_fd_exact_arg EXACT)
      endif()
      set(cmake_fd_quiet_arg)
      if(${CMAKE_FIND_PACKAGE_NAME}_FIND_QUIETLY)
        set(cmake_fd_quiet_arg QUIET)
      endif()
      set(cmake_fd_required_arg)
      if(${CMAKE_FIND_PACKAGE_NAME}_FIND_REQUIRED)
        set(cmake_fd_required_arg REQUIRED)
      endif()
      find_package(${dep} ${cmake_fd_version}
          ${cmake_fd_exact_arg}
          ${cmake_fd_quiet_arg}
          ${cmake_fd_required_arg}
      )
      string(TOUPPER ${dep} cmake_dep_upper)
      if (NOT ${dep}_FOUND AND NOT ${cmake_dep_upper}_FOUND)
        set(${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE "${CMAKE_FIND_PACKAGE_NAME} could not be found because dependency ${dep} could not be found.")
        set(${CMAKE_FIND_PACKAGE_NAME}_FOUND False)
        return()
      endif()
      set(cmake_fd_version)
      set(cmake_fd_required_arg)
      set(cmake_fd_quiet_arg)
      set(cmake_fd_exact_arg)
    endif()
  endmacro()
endif()

set(HIP_COMPILER "clang")
set(HIP_RUNTIME "rocclr")

include( "${CMAKE_CURRENT_LIST_DIR}/hip-lang-targets.cmake" )

# Find the hip-lang config file path with symlinks resolved
# RealPath: /opt/rocm-ver/lib/cmake/hip-lang/hip-lang-config.cmake
# Go 4 level up to get IMPORT PREFIX
get_filename_component(_DIR "${CMAKE_CURRENT_LIST_FILE}" REALPATH)
get_filename_component(_IMPORT_PREFIX "${_DIR}/../../../../" ABSOLUTE)


set_target_properties(hip-lang::device PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "$<$<COMPILE_LANGUAGE:HIP>:${_IMPORT_PREFIX}/include>"
  INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "$<$<COMPILE_LANGUAGE:HIP>:${_IMPORT_PREFIX}/include>"
)

set_target_properties(hip-lang::amdhip64 PROPERTIES
  INTERFACE_COMPILE_DEFINITIONS "$<$<COMPILE_LANGUAGE:HIP>:__HIP_ROCclr__=1>"
  INTERFACE_INCLUDE_DIRECTORIES "$<$<COMPILE_LANGUAGE:HIP>:${_IMPORT_PREFIX}/include>"
  INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "$<$<COMPILE_LANGUAGE:HIP>:${_IMPORT_PREFIX}/include>"
)
set_target_properties(hip-lang::device PROPERTIES
  INTERFACE_COMPILE_DEFINITIONS "$<$<COMPILE_LANGUAGE:HIP>:__HIP_ROCclr__=1>"
)

set_property(TARGET hip-lang::device APPEND PROPERTY
  INTERFACE_COMPILE_OPTIONS "$<$<COMPILE_LANGUAGE:HIP>:SHELL:-mllvm;-amdgpu-early-inline-all=true;-mllvm;-amdgpu-function-calls=false>"
)

set_property(TARGET hip-lang::device APPEND PROPERTY
  INTERFACE_LINK_OPTIONS "$<$<LINK_LANGUAGE:HIP>:--hip-link>"
)

# Approach: Check CLANGRT LIB support for CMAKE_HIP_COMPILER
# Use CMAKE_HIP_COMPILER option -print-libgcc-file-name --rtlib=compiler-rt
# Note: For Linux add additional option -unwindlib=libgcc also
# To fetch the compiler rt library file name and confirm.
# If unsuccessful in getting clangrt using this option then
# FATAL_ERROR message send since compiler-rt linkage dependency is mandatory.
# If successful then --rtlib=compiler-rt (and -unwindlib=libgcc for non windows)
# added to Target's INTERFACE_LINK_LIBRARIES property
if (NOT WIN32)
  set(CLANGRT_LINUX_OPTION "-unwindlib=libgcc")
endif()

execute_process(
  COMMAND ${CMAKE_HIP_COMPILER} -print-libgcc-file-name --rtlib=compiler-rt ${CLANGRT_LINUX_OPTION}
  OUTPUT_VARIABLE CLANGRT_BUILTINS
  OUTPUT_STRIP_TRAILING_WHITESPACE
  RESULT_VARIABLE CLANGRT_BUILTINS_FETCH_EXIT_CODE)

# Add support for __fp16 and _Float16, explicitly link with compiler-rt
if( "${CLANGRT_BUILTINS_FETCH_EXIT_CODE}" STREQUAL "0" )
  set_property(TARGET hip-lang::device APPEND PROPERTY
    INTERFACE_LINK_OPTIONS $<$<LINK_LANGUAGE:HIP>:--rtlib=compiler-rt ${CLANGRT_LINUX_OPTION}>
  )
else()
  # FATAL_ERROR send if not successfull on compiler-rt linkage dependency
  message(FATAL_ERROR
	"${CMAKE_FIND_PACKAGE_NAME} Error:${CLANGRT_BUILTINS_FETCH_EXIT_CODE} - clangrt builtins lib could not be found.")
endif()

# Approved by CMake to use this name. This is used so that HIP can
# change the name of the target and not require any modifications in CMake
set(_CMAKE_HIP_DEVICE_RUNTIME_TARGET "hip-lang::device")
