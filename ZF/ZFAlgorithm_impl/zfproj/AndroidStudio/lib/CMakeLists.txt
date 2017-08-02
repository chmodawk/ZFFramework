cmake_minimum_required(VERSION 3.4.1)

set(ZF_ROOT_PATH ${PROJECT_SOURCE_DIR}/../../../../../../ZFFramework)

file(GLOB_RECURSE zfsrc_c RELATIVE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/../../../zfsrc/*.c)
file(GLOB_RECURSE zfsrc_cpp RELATIVE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/../../../zfsrc/*.cpp)
file(GLOB_RECURSE zfsrc_ext_c RELATIVE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/../../../zfsrc_ext/*.c)
file(GLOB_RECURSE zfsrc_ext_cpp RELATIVE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/../../../zfsrc_ext/*.cpp)
add_library(ZFAlgorithm_impl SHARED
            ${zfsrc_c}
            ${zfsrc_cpp}
            ${zfsrc_ext_c}
            ${zfsrc_ext_cpp}
           )
set_target_properties(ZFAlgorithm_impl PROPERTIES LINKER_LANGUAGE CXX)

find_library(log-lib log)
find_library(android-lib android)
target_link_libraries(ZFAlgorithm_impl ${android-lib} ${log-lib})

include_directories(${PROJECT_SOURCE_DIR}/../../../zfsrc)
include_directories(${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/include)


add_library(ZFCore SHARED IMPORTED)
set_target_properties(ZFCore PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZFCore.so)
target_link_libraries(ZFAlgorithm_impl ZFCore)
add_library(ZFAlgorithm SHARED IMPORTED)
set_target_properties(ZFAlgorithm PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZFAlgorithm.so)
target_link_libraries(ZFAlgorithm_impl ZFAlgorithm)
add_library(ZF_impl SHARED IMPORTED)
set_target_properties(ZF_impl PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZF_impl.so)
target_link_libraries(ZFAlgorithm_impl ZF_impl)

