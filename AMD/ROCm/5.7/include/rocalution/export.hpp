
#ifndef ROCALUTION_EXPORT_H
#define ROCALUTION_EXPORT_H

#ifdef ROCALUTION_STATIC_DEFINE
#  define ROCALUTION_EXPORT
#  define ROCALUTION_NO_EXPORT
#else
#  ifndef ROCALUTION_EXPORT
#    ifdef rocalution_EXPORTS
        /* We are building this library */
#      define ROCALUTION_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define ROCALUTION_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef ROCALUTION_NO_EXPORT
#    define ROCALUTION_NO_EXPORT 
#  endif
#endif

#ifndef ROCALUTION_DEPRECATED
#  define ROCALUTION_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef ROCALUTION_DEPRECATED_EXPORT
#  define ROCALUTION_DEPRECATED_EXPORT ROCALUTION_EXPORT ROCALUTION_DEPRECATED
#endif

#ifndef ROCALUTION_DEPRECATED_NO_EXPORT
#  define ROCALUTION_DEPRECATED_NO_EXPORT ROCALUTION_NO_EXPORT ROCALUTION_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef ROCALUTION_NO_DEPRECATED
#    define ROCALUTION_NO_DEPRECATED
#  endif
#endif

#endif /* ROCALUTION_EXPORT_H */
