# Copyright (c) 2020 - 2021 Advanced Micro Devices, Inc. All Rights Reserved.
#
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
cmake_minimum_required(VERSION 3.3)


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was hip-config.cmake.in                            ########

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
include(CheckCXXCompilerFlag)
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

set(_HIP_SHELL "SHELL:")
if(CMAKE_VERSION VERSION_LESS 3.12)
  set(_HIP_SHELL "")
endif()

function(hip_add_interface_compile_flags TARGET)
  set_property(TARGET ${TARGET} APPEND PROPERTY
    INTERFACE_COMPILE_OPTIONS "$<$<COMPILE_LANGUAGE:CXX>:${_HIP_SHELL}${ARGN}>"
  )
endfunction()

function(hip_add_interface_link_flags TARGET)
  if(CMAKE_VERSION VERSION_LESS 3.20)
    set_property(TARGET ${TARGET} APPEND PROPERTY
      INTERFACE_LINK_LIBRARIES "${ARGN}"
    )
  else()
    set_property(TARGET ${TARGET} APPEND PROPERTY
      INTERFACE_LINK_LIBRARIES "$<$<LINK_LANGUAGE:CXX>:${ARGN}>"
    )
  endif()
endfunction()

# NOTE: If hip-config is invoked from /opt/rocm-ver/hip/lib/cmake/hip/
# then PACKAGE_PREFIX_DIR will resolve to /opt/rocm-ver/hip, which is for backward compatibility
# The following will ensure PACKAGE_PREFIX_DIR will resolves to /opt/rocm-ver
# First find the real path to hip-config file with symlinks resolved
# Real Path : /opt/rocm-ver/lib/cmake/hip/hip-config.cmake
# Then go up 4 levels to get PACKAGE_PREFIX_DIR
# PACKAGE_PREFIX_DIR : /opt/rocm-ver
# TODO:once file reorg backward compatibility is turned off this can be removed.
if(IS_SYMLINK ${CMAKE_CURRENT_LIST_FILE})
  get_filename_component(CONFIG_FILE_PATH "${CMAKE_CURRENT_LIST_FILE}" REALPATH)
  get_filename_component(PACKAGE_PREFIX_DIR "${CONFIG_FILE_PATH}/../../../../" ABSOLUTE)
endif()
# end of TODO
set(HIP_PACKAGE_PREFIX_DIR  ${PACKAGE_PREFIX_DIR})

set_and_check( hip_INCLUDE_DIR "${PACKAGE_PREFIX_DIR}/include" )
set_and_check( hip_INCLUDE_DIRS "${hip_INCLUDE_DIR}" )
set_and_check( hip_LIB_INSTALL_DIR "${PACKAGE_PREFIX_DIR}/lib" )
set_and_check( hip_BIN_INSTALL_DIR "${PACKAGE_PREFIX_DIR}/bin" )
if(WIN32)
  set_and_check(hip_HIPCC_EXECUTABLE "${hip_BIN_INSTALL_DIR}/hipcc.bat")
  set_and_check(hip_HIPCONFIG_EXECUTABLE "${hip_BIN_INSTALL_DIR}/hipconfig.bat")
else()
  set_and_check(hip_HIPCC_EXECUTABLE "${hip_BIN_INSTALL_DIR}/hipcc")
  set_and_check(hip_HIPCONFIG_EXECUTABLE "${hip_BIN_INSTALL_DIR}/hipconfig")
endif()

if(NOT DEFINED HIP_PLATFORM)
  if(NOT DEFINED ENV{HIP_PLATFORM})
    execute_process(COMMAND ${hip_HIPCONFIG_EXECUTABLE} --platform
      OUTPUT_VARIABLE HIP_PLATFORM
      OUTPUT_STRIP_TRAILING_WHITESPACE)
  else()
    set(HIP_PLATFORM $ENV{HIP_PLATFORM} CACHE STRING "HIP Platform")
  endif()
endif()

if(HIP_PLATFORM STREQUAL "amd")
  set(HIP_RUNTIME "rocclr")
  set(HIP_COMPILER "clang")
  include( "${hip_LIB_INSTALL_DIR}/cmake/hip/hip-config-amd.cmake" )
elseif(HIP_PLATFORM STREQUAL "nvidia")
  set(HIP_RUNTIME "cuda")
  set(HIP_COMPILER "nvcc")
  include( "${hip_LIB_INSTALL_DIR}/cmake/hip/hip-config-nvidia.cmake" )
else()
  message(FATAL_ERROR "Unexpected HIP_PLATFORM: " ${HIP_PLATFORM})
endif()

set( hip_LIBRARIES hip::host hip::device)
set( hip_LIBRARY ${hip_LIBRARIES})

set(HIP_INCLUDE_DIR ${hip_INCLUDE_DIR})
set(HIP_INCLUDE_DIRS ${hip_INCLUDE_DIRS})
set(HIP_LIB_INSTALL_DIR ${hip_LIB_INSTALL_DIR})
set(HIP_BIN_INSTALL_DIR ${hip_BIN_INSTALL_DIR})
set(HIP_LIBRARIES ${hip_LIBRARIES})
set(HIP_LIBRARY ${hip_LIBRARY})
set(HIP_HIPCC_EXECUTABLE ${hip_HIPCC_EXECUTABLE})
set(HIP_HIPCONFIG_EXECUTABLE ${hip_HIPCONFIG_EXECUTABLE})

