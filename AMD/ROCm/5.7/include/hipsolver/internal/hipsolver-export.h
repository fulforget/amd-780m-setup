
#ifndef HIPSOLVER_EXPORT_H
#define HIPSOLVER_EXPORT_H

#ifdef HIPSOLVER_STATIC_DEFINE
#  define HIPSOLVER_EXPORT
#  define HIPSOLVER_NO_EXPORT
#else
#  ifndef HIPSOLVER_EXPORT
#    ifdef hipsolver_EXPORTS
        /* We are building this library */
#      define HIPSOLVER_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define HIPSOLVER_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef HIPSOLVER_NO_EXPORT
#    define HIPSOLVER_NO_EXPORT 
#  endif
#endif

#ifndef HIPSOLVER_DEPRECATED
#  define HIPSOLVER_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef HIPSOLVER_DEPRECATED_EXPORT
#  define HIPSOLVER_DEPRECATED_EXPORT HIPSOLVER_EXPORT HIPSOLVER_DEPRECATED
#endif

#ifndef HIPSOLVER_DEPRECATED_NO_EXPORT
#  define HIPSOLVER_DEPRECATED_NO_EXPORT HIPSOLVER_NO_EXPORT HIPSOLVER_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef HIPSOLVER_NO_DEPRECATED
#    define HIPSOLVER_NO_DEPRECATED
#  endif
#endif

#endif /* HIPSOLVER_EXPORT_H */
