# Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
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

# hiprand-config.cmake
# ---------
#
# Finds hipRAND include directory and library.
#
# Use this module by invoking find_package with the form:
#
#   find_package(hiprand
#     [version] [EXACT]           # Minimum or EXACT version e.g. 0.5.0
#     [REQUIRED]                  # Fail with error if hipRAND is not found
#     CONFIG                      # Enable Config mode (might be required)
#     [PATHS path1 [path2 ... ]]  # Path to install dir (e.g. /opt/rocm/hiprand)
#   )                        #
#
# The following variables are defined when hipRAND is found:
#
#   hiprand_FOUND            - True if hipRAND headers and library were found.
#   hiprand_INCLUDE_DIRS     - hipRAND include directory.
#   hiprand_LIBRARY_DIRS     - Link directory for hipRAND library.
#   hiprand_LIBRARIES        - hipRAND library to be linked.
#   hiprand_VERSION          - HIPRAND_VERSION value from hiprand.h.
#
#   hiprand_FORTRAN_FOUND    - True if hipRAND was built with Fortran wrapper; otherwise - false.
#   hiprand_FORTRAN_SRC_DIRS - Directory with hipRAND Fortran wrapper sources hiprand_m.f90
#                              and hip_m.f90. Include those source files, and add "use hiprand_m"
#                              statement into your Fortran code.
#
#
# Example (requires HIP, and rocRAND or cuRAND):
#
#    // Remember to first find and include HIP
#    // See https://github.com/ROCm-Developer-Tools/HIP
#    find_package(hiprand REQUIRED CONFIG PATHS "/opt/rocm/hiprand")
#    if(HIP_PLATFORM STREQUAL "hcc")
#      find_package(rocrand REQUIRED CONFIG PATHS "/opt/rocm/rocrand")
#    endif()
#
#    add_executable(foo foo.cpp)
#    // Set HIP flags, includes (see hipconfig)
#    if(HIP_PLATFORM STREQUAL "hcc")
#      // Link foo against HIP library
#      target_link_libraries(foo roc::rocrand hip::hiprand)
#    else()
#      // Link foo against CUDA library
#      target_link_libraries(foo "-lcurand" hip::hiprand)
#    endif()
#
#    # Using Fortran wrapper
#    set(bar_SRCS
#      bar.f90
#      /hip_m.f90
#      /hiprand_m.f90
#    )
#
#    add_executable(bar )
#    if(HIP_PLATFORM STREQUAL "hcc")
#      // Link bar against HIP library
#      target_link_libraries(bar roc::rocrand hip::hiprand)
#    else()
#      // Link bar against CUDA libraries
#      target_link_libraries(bar "-lcurand" hip::hiprand)
#    endif()
#

# Fortran wrapper
if(OFF)
    set_and_check(hiprand_FORTRAN_SRC_DIR "C:/hipSDK/hiprand/src/fortran")
    set_and_check(hiprand_FORTRAN_SRC_DIRS "C:/hipSDK/hiprand/src/fortran")
    set(hiprand_FORTRAN_FOUND YES)
else()
    set(hiprand_FORTRAN_FOUND NOTFOUND)
endif()
