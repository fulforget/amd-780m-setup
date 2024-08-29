
#ifndef ROCFFT_EXPORT_H
#define ROCFFT_EXPORT_H

#ifdef ROCFFT_STATIC_DEFINE
#  define ROCFFT_EXPORT
#  define ROCFFT_NO_EXPORT
#else
#  ifndef ROCFFT_EXPORT
#    ifdef rocfft_EXPORTS
        /* We are building this library */
#      define ROCFFT_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define ROCFFT_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef ROCFFT_NO_EXPORT
#    define ROCFFT_NO_EXPORT 
#  endif
#endif

#ifndef ROCFFT_DEPRECATED
#  define ROCFFT_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef ROCFFT_DEPRECATED_EXPORT
#  define ROCFFT_DEPRECATED_EXPORT ROCFFT_EXPORT ROCFFT_DEPRECATED
#endif

#ifndef ROCFFT_DEPRECATED_NO_EXPORT
#  define ROCFFT_DEPRECATED_NO_EXPORT ROCFFT_NO_EXPORT ROCFFT_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef ROCFFT_NO_DEPRECATED
#    define ROCFFT_NO_DEPRECATED
#  endif
#endif

#endif /* ROCFFT_EXPORT_H */
