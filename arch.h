
#ifndef _JSAHN_ARCH_H
#define _JSAHN_ARCH_H

#include <stdio.h>
#include <fcntl.h>
#include <inttypes.h>

#ifdef __APPLE__
    #define INLINE extern inline

    #define _F64 "lld"
    #define _FSEC "ld"
    #define _FUSEC "d"

    #define _ARCH_O_DIRECT (0x0)

    #define malloc_align(addr, align, size) \
        int __ret__ = posix_memalign(&(addr), (align), (size))
    #define free_align(addr) free(addr)

    #ifndef spin_t
        // spinlock
        #include <libkern/OSAtomic.h>
        #define spin_t OSSpinLock
        #define spin_lock(arg) OSSpinLockLock(arg)
        #define spin_unlock(arg) OSSpinLockUnlock(arg)
        #define SPIN_INITIALIZER (spin_t)(0)
        #define spin_init(arg) *(arg) = (spin_t)(0)
        #define spin_destroy(arg)
    #endif
    #ifndef mutex_t
        // mutex
        #include <pthread.h>
        #define mutex_t pthread_mutex_t
        #define mutex_init(arg) pthread_mutex_init(arg, NULL)
        #define mutex_lock(arg) pthread_mutex_lock(arg)
        #define mutex_unlock(arg) pthread_mutex_unlock(arg)
        #define MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER
        #define mutex_destroy(arg) pthread_mutex_destroy(arg)
    #endif
    #ifndef thread_t
            // thread
        #include <pthread.h>
        #define thread_t pthread_t
        #define thread_create(tid, func, args) \
            pthread_create((tid), NULL, (func), (args))
        #define thread_join(tid, ret) pthread_join(tid, ret)
        #define thread_exit(code) pthread_exit(code)
    #endif

#elif __linux__
    #define INLINE __inline

    #define _F64 PRIu64
    #define _FSEC "ld"
    #define _FUSEC "ld"

    #define _ARCH_O_DIRECT (O_DIRECT)

    #define malloc_align(addr, align, size) \
        addr = memalign((align), (size))
    #define free_align(addr) free(addr)

    #ifndef spin_t
        // spinlock
        #include <pthread.h>
        #define spin_t pthread_spinlock_t
        #define spin_init(arg) pthread_spin_init(arg, PTHREAD_PROCESS_SHARED)
        #define spin_lock(arg) pthread_spin_lock(arg)
        #define spin_unlock(arg) pthread_spin_unlock(arg)
        #define spin_destroy(arg) pthread_spin_destroy(arg)
        #define SPIN_INITIALIZER (spin_t)(1)
    #endif
    #ifndef mutex_t
        // mutex
        #include <pthread.h>
        #define mutex_t pthread_mutex_t
        #define mutex_init(arg) pthread_mutex_init(arg, NULL)
        #define mutex_lock(arg) pthread_mutex_lock(arg)
        #define mutex_unlock(arg) pthread_mutex_unlock(arg)
        #define MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER
        #define mutex_destroy(arg) pthread_mutex_destroy(arg)
    #endif
    #ifndef thread_t
        // thread
        #include <pthread.h>
        #define thread_t pthread_t
        #define thread_create(tid, func, args) \
            pthread_create((tid), NULL, (func), (args))
        #define thread_join(tid, ret) pthread_join(tid, ret)
        #define thread_exit(code) pthread_exit(code)
    #endif

#elif defined(WIN32) || defined(_WIN32)
    // mingw compatiable
    #define INLINE __inline

    #define _F64 PRIu64
    #define _FSEC "ld"
    #define _FUSEC "ld"

    #define _ARCH_O_DIRECT (0x0)

    #include <windows.h>
    #include <stdlib.h>
    #define malloc_align(addr, align, size) \
        addr = (void*)_aligned_malloc((size), (align))
    #define free_align(addr) _aligned_free(addr)

    #ifndef spin_t
        // spinlock
        #define spin_t CRITICAL_SECTION
        #define spin_init(arg) InitializeCriticalSection(arg)
        #define spin_lock(arg) EnterCriticalSection(arg)
        #define spin_unlock(arg) LeaveCriticalSection(arg)
        #define spin_destroy(arg) DeleteCriticalSection(arg)
    #endif
    #ifndef mutex_t
        // mutex
        #define mutex_t CRITICAL_SECTION
        #define mutex_init(arg) InitializeCriticalSection(arg)
        #define mutex_lock(arg) EnterCriticalSection(arg)
        #define mutex_unlock(arg) LeaveCriticalSection(arg)
        #define mutex_destroy(arg) DeleteCriticalSection(arg)
    #endif
    #ifndef thread_t
        // thread
        #define thread_t HANDLE
        #define thread_create(tid, func, args) \
            { \
            DWORD __dt__; \
            *(tid) = CreateThread(NULL, 0, \
                (LPTHREAD_START_ROUTINE)(func), (args), 0, &__dt__); \
            }
        #define thread_join(tid, ret) WaitForSingleObject(tid, INFINITE)
        #define thread_exit(code) ExitThread(code)
    #endif

#elif __CYGWIN__
    // cygwin compatiable
    #define INLINE __inline

    #define _F64 PRIu64
    #define _FSEC "ld"
    #define _FUSEC "ld"

    #define _ARCH_O_DIRECT (0x0)

    #define malloc_align(addr, align, size) \
        addr = memalign((align), (size))
    #define free_align(addr) free(addr)

    #ifndef spin_t
        // spinlock
        #include <pthread.h>
        #define spin_t pthread_spinlock_t
        #define spin_init(arg) pthread_spin_init(arg, PTHREAD_PROCESS_SHARED)
        #define spin_lock(arg) pthread_spin_lock(arg)
        #define spin_unlock(arg) pthread_spin_unlock(arg)
        #define spin_destroy(arg) pthread_spin_destroy(arg)
        #define SPIN_INITIALIZER (spin_t)(1)
    #endif
    #ifndef mutex_t
        // mutex
        #include <pthread.h>
        #define mutex_t pthread_mutex_t
        #define mutex_init(arg) pthread_mutex_init(arg, NULL)
        #define mutex_lock(arg) pthread_mutex_lock(arg)
        #define mutex_unlock(arg) pthread_mutex_unlock(arg)
        #define MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER
        #define mutex_destroy(arg) pthread_mutex_destroy(arg)
    #endif
    #ifndef thread_t
        // thread
        #include <pthread.h>
        #define thread_t pthread_t
        #define thread_create(tid, func, args) \
            pthread_create((tid), NULL, (func), (args))
        #define thread_join(tid, ret) pthread_join(tid, ret)
        #define thread_exit(code) pthread_exit(code)
    #endif

#else
    #define INLINE make_error
#endif


#endif
