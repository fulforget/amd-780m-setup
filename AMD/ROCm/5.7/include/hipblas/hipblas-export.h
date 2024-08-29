
#ifndef HIPBLAS_EXPORT_H
#define HIPBLAS_EXPORT_H

#ifdef HIPBLAS_STATIC_DEFINE
#  define HIPBLAS_EXPORT
#  define HIPBLAS_NO_EXPORT
#else
#  ifndef HIPBLAS_EXPORT
#    ifdef hipblas_EXPORTS
        /* We are building this library */
#      define HIPBLAS_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define HIPBLAS_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef HIPBLAS_NO_EXPORT
#    define HIPBLAS_NO_EXPORT 
#  endif
#endif

#ifndef HIPBLAS_DEPRECATED
#  define HIPBLAS_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef HIPBLAS_DEPRECATED_EXPORT
#  define HIPBLAS_DEPRECATED_EXPORT HIPBLAS_EXPORT HIPBLAS_DEPRECATED
#endif

#ifndef HIPBLAS_DEPRECATED_NO_EXPORT
#  define HIPBLAS_DEPRECATED_NO_EXPORT HIPBLAS_NO_EXPORT HIPBLAS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef HIPBLAS_NO_DEPRECATED
#    define HIPBLAS_NO_DEPRECATED
#  endif
#endif

#endif /* HIPBLAS_EXPORT_H */
