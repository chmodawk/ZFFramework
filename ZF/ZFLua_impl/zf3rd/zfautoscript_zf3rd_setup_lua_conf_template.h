
// add by ZFFramework
// Android's NDK does not support this
#if defined(ANDROID) || defined(__ANDROID__)
    #undef lua_getlocaledecpoint
    #define lua_getlocaledecpoint() ('.')
#endif

