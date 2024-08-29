
#ifndef ROCSOLVER_EXPORT_H
#define ROCSOLVER_EXPORT_H

#ifdef ROCSOLVER_STATIC_DEFINE
#  define ROCSOLVER_EXPORT
#  define ROCSOLVER_NO_EXPORT
#else
#  ifndef ROCSOLVER_EXPORT
#    ifdef rocsolver_EXPORTS
        /* We are building this library */
#      define ROCSOLVER_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define ROCSOLVER_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef ROCSOLVER_NO_EXPORT
#    define ROCSOLVER_NO_EXPORT 
#  endif
#endif

#ifndef ROCSOLVER_DEPRECATED
#  define ROCSOLVER_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef ROCSOLVER_DEPRECATED_EXPORT
#  define ROCSOLVER_DEPRECATED_EXPORT ROCSOLVER_EXPORT ROCSOLVER_DEPRECATED
#endif

#ifndef ROCSOLVER_DEPRECATED_NO_EXPORT
#  define ROCSOLVER_DEPRECATED_NO_EXPORT ROCSOLVER_NO_EXPORT ROCSOLVER_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef ROCSOLVER_NO_DEPRECATED
#    define ROCSOLVER_NO_DEPRECATED
#  endif
#endif

#endif /* ROCSOLVER_EXPORT_H */
