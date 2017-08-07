cmake_minimum_required(VERSION 3.4.1)

set(ZF_ROOT_PATH ${PROJECT_SOURCE_DIR}/../../../../../ZFFramework)

file(GLOB_RECURSE zfsrc_c RELATIVE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/../../../zfsrc/*.c)
file(GLOB_RECURSE zfsrc_cpp RELATIVE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/../../../zfsrc/*.cpp)
file(GLOB_RECURSE zfsrc_ext_c RELATIVE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/../../../zfsrc_ext/*.c)
file(GLOB_RECURSE zfsrc_ext_cpp RELATIVE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/../../../zfsrc_ext/*.cpp)
add_library(ZF2048 SHARED
            ${zfsrc_c}
            ${zfsrc_cpp}
            ${zfsrc_ext_c}
            ${zfsrc_ext_cpp}
           )
set_target_properties(ZF2048 PROPERTIES LINKER_LANGUAGE CXX)

find_library(log-lib log)
find_library(android-lib android)
target_link_libraries(ZF2048 ${android-lib} ${log-lib})

include_directories(${PROJECT_SOURCE_DIR}/../../../zfsrc)
include_directories(${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/include)


add_library(ZFCore SHARED IMPORTED)
set_target_properties(ZFCore PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZFCore.so)
target_link_libraries(ZF2048 ZFCore)
add_library(ZFAlgorithm SHARED IMPORTED)
set_target_properties(ZFAlgorithm PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZFAlgorithm.so)
target_link_libraries(ZF2048 ZFAlgorithm)
add_library(ZFUtility SHARED IMPORTED)
set_target_properties(ZFUtility PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZFUtility.so)
target_link_libraries(ZF2048 ZFUtility)
add_library(ZFUIKit SHARED IMPORTED)
set_target_properties(ZFUIKit PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZFUIKit.so)
target_link_libraries(ZF2048 ZFUIKit)
add_library(ZFAddition SHARED IMPORTED)
set_target_properties(ZFAddition PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZFAddition.so)
target_link_libraries(ZF2048 ZFAddition)
add_library(ZFUIWidget SHARED IMPORTED)
set_target_properties(ZFUIWidget PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZFUIWidget.so)
target_link_libraries(ZF2048 ZFUIWidget)
add_library(ZF_impl SHARED IMPORTED)
set_target_properties(ZF_impl PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZF_impl.so)
target_link_libraries(ZF2048 ZF_impl)
add_library(ZF_loader_impl SHARED IMPORTED)
set_target_properties(ZF_loader_impl PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZF_loader_impl.so)
target_link_libraries(ZF2048 ZF_loader_impl)
add_library(ZFCore_impl SHARED IMPORTED)
set_target_properties(ZFCore_impl PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZFCore_impl.so)
target_link_libraries(ZF2048 ZFCore_impl)
add_library(ZFAlgorithm_impl SHARED IMPORTED)
set_target_properties(ZFAlgorithm_impl PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZFAlgorithm_impl.so)
target_link_libraries(ZF2048 ZFAlgorithm_impl)
add_library(ZFUIKit_impl SHARED IMPORTED)
set_target_properties(ZFUIKit_impl PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZFUIKit_impl.so)
target_link_libraries(ZF2048 ZFUIKit_impl)

