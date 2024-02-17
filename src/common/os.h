// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef DPP_COMMON_TYPE_OS_H_
#define DPP_COMMON_TYPE_OS_H_

#ifdef _WIN32
#define DPP_WINDOWS
#endif  // _WIN32

#ifdef __linux__
#define DPP_LINUX
#endif  // __linux__

#ifdef __APPLE__
#define DPP_APPLE
#endif  // __APPLE__

#if defined __linux__ || defined __APPLE__ || defined __sun || \
    defined __FreeBSD__ || defined __NetBSD__ || defined __OpenBSD__
#define DPP_UNIX
#endif  // __linux__ || defined __APPLE__ || defined __sun || __FreeBSD__ ||
        // defined __NetBSD__ || defined __OpenBSD__

#ifdef DPP_WINDOWS
#ifdef _WIN64
#define DPP_64
#else
#define DPP_32
#endif  // _WIN64
#endif  // DPP_WINDOWS

// Check GCC
#if defined DPP_UNIX || defined DPP_APPLE
#if __x86_64__ || __ppc64__
#define DPP_64
#else
#define DPP_32
#endif
#endif  // defined DPP_UNIX || defined DPP_APPLE

#endif  // DPP_COMMON_TYPE_OS_H_