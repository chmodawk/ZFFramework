project should follow this structure:

(`~` stands for root path of ZFFramework)

```
// for ZF libs
~/ZF/LibName/
    zfproj/
        Android/
            LibName_jni/
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
            ImplLibName_impl_jni/
        iOS/
            ImplLibName_impl/
                ImplLibName_impl.xcodeproj/
        Qt/
            ImplLibName_impl/
                ImplLibName_impl.pro
    zfres/
    zfsrc/
```

