
#ifndef ROCBLAS_EXPORT_H
#define ROCBLAS_EXPORT_H

#ifdef ROCBLAS_STATIC_DEFINE
#  define ROCBLAS_EXPORT
#  define ROCBLAS_NO_EXPORT
#else
#  ifndef ROCBLAS_EXPORT
#    ifdef rocblas_EXPORTS
        /* We are building this library */
#      define ROCBLAS_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define ROCBLAS_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef ROCBLAS_NO_EXPORT
#    define ROCBLAS_NO_EXPORT 
#  endif
#endif

#ifndef ROCBLAS_DEPRECATED
#  define ROCBLAS_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef ROCBLAS_DEPRECATED_EXPORT
#  define ROCBLAS_DEPRECATED_EXPORT ROCBLAS_EXPORT ROCBLAS_DEPRECATED
#endif

#ifndef ROCBLAS_DEPRECATED_NO_EXPORT
#  define ROCBLAS_DEPRECATED_NO_EXPORT ROCBLAS_NO_EXPORT ROCBLAS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef ROCBLAS_NO_DEPRECATED
#    define ROCBLAS_NO_DEPRECATED
#  endif
#endif

#endif /* ROCBLAS_EXPORT_H */
