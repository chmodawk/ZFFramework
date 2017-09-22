# project dir structure

```
// for ZF libs
~/ZF/LibName/
    zfproj/
        Android/
            LibName/
                gradle/
                jni_LibName/
                    src/
                    build.gradle
                    CMakeLists.txt
                build.gradle
        iOS/
            LibName/
                LibName.xcodeproj/
        Qt/
            LibName/
                LibName.pro
    zfres/
    zfsrc/

// for ZF impl libs
~/ZF/ImplLibName_impl/
    zfproj/
        Android/
            ImplLibName_impl/
                gradle/
                jni_ImplLibName_impl/
                    src/
                    build.gradle
                    CMakeLists.txt
                build.gradle
        iOS/
            ImplLibName_impl/
                ImplLibName_impl.xcodeproj/
        Qt/
            ImplLibName_impl/
                ImplLibName_impl.pro
    zfres/
    zfsrc/
```

# release dir structure

```
~/_release/
    Android/
        all/
        module/
            LibName/
                libs/
                    include/
                    libs/
                        armeabi/
                            libLibName.so
                    LibName.jar
                src/
                    main/
                        assets/
    iOS/
        all/
        module/
            LibName/
                include/
                lib/
                    libLibName.a
                zfres/
    Qt_MacOS/
    Qt_Posix
    Qt_Windows/
        all/
        module/
            LibName/
                include/
                lib/
                    libLibName.[a|so|dll|dylib]
                zfres/
```

