# Intro

this file is written as a note for developers that want to know the mechanism of ZFFramework

# Contents

## Abbreviations

there are many abbreviations in ZFFramework which keep code style and you should follow:

* `_ZFP_` : `ZF Private` contents, should not be used for public
* `_ZFP_I_` : `ZF Private Internal` contents, which won't be logged by global observers and leak tests
* `_ZFI_` : `ZF Include`, dummy macro to wrap headers
* `_ZFT_` : `ZF Type`, used to mark macro defined types
* `zft_` : `ZF Type`, primitive type wrapper
* `zfs` : `ZF String`, core string utils
* `zfm` : `ZF Math`, core math utils
* `zft` : `ZF Template`, core template utils
* `ZFM` : `ZF Macro`, core macro utils


## ZFCastZFObject

we use ZFCastZFObject for dynamic type cast, instead of traditional dynamic_cast

the main reason for that is the performance, ZFFramework use multi-inheritance to simulate interface logic,
which would cause deep inherit tree, which cause dynamic_cast to be very slow

secondly, it reduce the dependency of RTTI, which is not much necessary for ZFFramework


## class namespace

since written in C++, raw namespace are supported, however,
ZFClass has no namespace support, and it's designed to be so, because:

* string operations are slow, especially under ZFFramework's heavily serialization and styleable logic,
    having namespace support would cause huge increased string concatenate and split operations


## STL dependency

we require STL containers internally, but we ensure there's no STL contents would be exported,
and it's recommended not to abuse STL in ZFFramework

the main reason is, it's a pain to export STL types,
especially for different STL versions when linking


## string type

we use zfstring as low level string container, which is reproduce of std::string

* to reduce dependency for STL, usually it's a pain to export STL containers because of different STL versions
* behaviors changed:
    * able to construct from a null char string
    * NO thread-safe supported,
        which should be implemented manually,
        for most case, outter invoker should have wrapped by zfCoreMutexLocker,
        and there's no need for low level string types to supply thread-safe

for app level, we use ZFString/ZFStringEditable to hold strings,
whose actual impl depends on platform impl,
and may have better performance when integrated with UI
(considering a UI text view holding a large amount of text)

in short, zfstring is more convenient in cpp wolrd and has better performance for small string operations,
while ZFString suits the situation that interacting with native impls


## ZFCoreArray/ZFCoreMap

we use ZFCoreArray as low level array/list container, and ZFCoreMap for map/unordered_map,
mainly to reduce dependency for STL

however, the performance is not so good comparing to STL containers,
for performance, we would still use STL containers as internal types,
but make sure it won't be visible to public interface


## Styles

ZFFramework supply powerful serialization and style logic,
however, it cost much CPU for property comparing and copying

so, for performance, most of styleable object won't copy it's default style during init,
and most of default style are hard coded, only images are loaded from resource


## Reflection

all ZFClass/ZFMethod/ZFProperty are reflectable,
which are all implemented by callback functions

however, we have no direct support to export and make global vars serializable,
mainly to reduce complex rate of impl

to export global vars, we use `ZFEXPORT_VAR_DECLARE` / `ZFEXPORT_ENUM_DEFINE`,
which is actually a wrapper to ZFMethod


## script binding

since ZFFramework support reflection,
we are trying hard to achive script binding by reflection dynamically and automatically

1. all non-ZFObject type should be registered by `ZFPROPERTY_TYPE_DECLARE`
1. all ZFMethod supply a generic invoker (`ZFMethod::methodGenericInvoker`)
    that takes base ZFObject as param and invoke the original method
1. use reflection, to bind the generic invoker to scrypt languages dynamically
1. the final script language should look like

    ```
    var obj = MyZFObjectType::zfAlloc();
    var objParam = zfAlloc("SomeType");
    var result = obj.myFunc(zfint(1), zfstring("2"), YourType("encodedData"), objParam);
    var result = obj.myFunc(1, "2", "encodedData", objParam);
    ```

    1. `zfAlloc` should be binded automatically by reflecting all `ZFClass` types
    1. `YourType` would be binded by ZFPROPERTY_TYPE_DECLARE series
    1. `YourType` can be serialized from encoded string data if it's serializable
      (declared by ZFPROPERTY_TYPE_DECLARE)
    1. `myFunc` should be binded automatically by reflecting all `ZFMethod` from `ZFClass` types
    1. finally, `myFunc` would be invoked with all ZFObject type as params and result

