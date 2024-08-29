
#ifndef HIPFFT_EXPORT_H
#define HIPFFT_EXPORT_H

#ifdef HIPFFT_STATIC_DEFINE
#  define HIPFFT_EXPORT
#  define HIPFFT_NO_EXPORT
#else
#  ifndef HIPFFT_EXPORT
#    ifdef hipfft_EXPORTS
        /* We are building this library */
#      define HIPFFT_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define HIPFFT_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef HIPFFT_NO_EXPORT
#    define HIPFFT_NO_EXPORT 
#  endif
#endif

#ifndef HIPFFT_DEPRECATED
#  define HIPFFT_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef HIPFFT_DEPRECATED_EXPORT
#  define HIPFFT_DEPRECATED_EXPORT HIPFFT_EXPORT HIPFFT_DEPRECATED
#endif

#ifndef HIPFFT_DEPRECATED_NO_EXPORT
#  define HIPFFT_DEPRECATED_NO_EXPORT HIPFFT_NO_EXPORT HIPFFT_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef HIPFFT_NO_DEPRECATED
#    define HIPFFT_NO_DEPRECATED
#  endif
#endif

#endif /* HIPFFT_EXPORT_H */
