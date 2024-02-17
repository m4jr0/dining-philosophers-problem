// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef DPP_COMMON_COMPILER_H_
#define DPP_COMMON_COMPILER_H_

#ifdef __clang__
#define DPP_CLANG
#elif defined(__GNUC__)
#define DPP_GCC
#ifdef __GNUG__
#define DPP_GCC_CPP
#else
#define DPP_GCC_C
#endif  // __GNUG__
#elif defined(_MSC_VER)
#define DPP_MSVC
#endif  // __clang__

#ifdef __cplusplus
#define DPP_CPP
#else
#define DPP_C
#endif  // __cplusplus

#endif  // DPP_COMMON_COMPILER_H_