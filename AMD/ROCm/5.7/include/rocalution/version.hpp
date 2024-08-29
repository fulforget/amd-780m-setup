/* ************************************************************************
 * Copyright (C) 2018-2020 Advanced Micro Devices, Inc. All rights Reserved.
 *
 * ************************************************************************ */

#ifndef ROCALUTION_VERSION_HPP_
#define ROCALUTION_VERSION_HPP_

// clang-format off
#define __ROCALUTION_VER_MAJOR     2
#define __ROCALUTION_VER_MINOR     1
#define __ROCALUTION_VER_PATCH     11
#define __ROCALUTION_VER_TWEAK     7a5f675-dirty
// clang-format on

// BETA or ALPHA
#define __ROCALUTION_VER_PRE ""
//#define __ROCALUTION_VER_PRE "ALPHA"
//#define __ROCALUTION_VER_PRE "BETA"

#define __ROCALUTION_VER \
    10000 * __ROCALUTION_VER_MAJOR + 100 * __ROCALUTION_VER_MINOR + __ROCALUTION_VER_PATCH

#endif // ROCALUTION_VERSION_HPP_
