// Copyright (c) 2017-2020 Advanced Micro Devices, Inc. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef ROCPRIM_VERSION_HPP_
#define ROCPRIM_VERSION_HPP_

/// \def ROCPRIM_VERSION
/// \brief ROCPRIM library version
///
/// Version number may not be visible in the documentation.
///
/// ROCPRIM_VERSION % 100 is the patch level,
/// ROCPRIM_VERSION / 100 % 1000 is the minor version,
/// ROCPRIM_VERSION / 100000 is the major version.
///
/// For example, if ROCPRIM_VERSION is 100500, then the major version is 1,
/// the minor version is 5, and the patch level is 0.
#define ROCPRIM_VERSION 2 * 100000 + 13 * 100 + 1

#define ROCPRIM_VERSION_MAJOR 2
#define ROCPRIM_VERSION_MINOR 13
#define ROCPRIM_VERSION_PATCH 1

#endif // ROCPRIM_VERSION_HPP_
