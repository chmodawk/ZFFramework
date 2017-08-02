cmake_minimum_required(VERSION 3.4.1)

set(ZF_ROOT_PATH ${PROJECT_SOURCE_DIR}/../../../../../ZFFramework)

file(GLOB_RECURSE zfsrc_c RELATIVE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/../../../zfsrc/*.c)
file(GLOB_RECURSE zfsrc_cpp RELATIVE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/../../../zfsrc/*.cpp)
file(GLOB_RECURSE zfsrc_ext_c RELATIVE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/../../../zfsrc_ext/*.c)
file(GLOB_RECURSE zfsrc_ext_cpp RELATIVE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/../../../zfsrc_ext/*.cpp)
add_library(ZFFramework_test SHARED
            ${zfsrc_c}
            ${zfsrc_cpp}
            ${zfsrc_ext_c}
            ${zfsrc_ext_cpp}
           )
set_target_properties(ZFFramework_test PROPERTIES LINKER_LANGUAGE CXX)

find_library(log-lib log)
find_library(android-lib android)
target_link_libraries(ZFFramework_test ${android-lib} ${log-lib})

include_directories(${PROJECT_SOURCE_DIR}/../../../zfsrc)
include_directories(${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/include)

if(CMAKE_HOST_WIN32)
    set(ZF_COPY_RES call ${ZF_ROOT_PATH}/tools/common/copy_check.bat)
else()
    set(ZF_COPY_RES sh ${ZF_ROOT_PATH}/tools/common/copy_check.sh)
endif()
add_custom_command(TARGET ZFFramework_test PRE_BUILD COMMAND
    ${ZF_COPY_RES} ${PROJECT_SOURCE_DIR}/../../../zfres ${PROJECT_SOURCE_DIR}/src/main/assets/zfres)


add_custom_command(TARGET ZFFramework_test PRE_BUILD COMMAND
    ${ZF_COPY_RES} ${ZF_ROOT_PATH}/_release/AndroidStudio/module/ZFCore/src/main/assets ${PROJECT_SOURCE_DIR}/src/main/assets)
add_library(ZFCore SHARED IMPORTED)
set_target_properties(ZFCore PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZFCore.so)
target_link_libraries(ZFFramework_test ZFCore)
add_custom_command(TARGET ZFFramework_test PRE_BUILD COMMAND
    ${ZF_COPY_RES} ${ZF_ROOT_PATH}/_release/AndroidStudio/module/ZFAlgorithm/src/main/assets ${PROJECT_SOURCE_DIR}/src/main/assets)
add_library(ZFAlgorithm SHARED IMPORTED)
set_target_properties(ZFAlgorithm PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZFAlgorithm.so)
target_link_libraries(ZFFramework_test ZFAlgorithm)
add_custom_command(TARGET ZFFramework_test PRE_BUILD COMMAND
    ${ZF_COPY_RES} ${ZF_ROOT_PATH}/_release/AndroidStudio/module/ZFUtility/src/main/assets ${PROJECT_SOURCE_DIR}/src/main/assets)
add_library(ZFUtility SHARED IMPORTED)
set_target_properties(ZFUtility PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZFUtility.so)
target_link_libraries(ZFFramework_test ZFUtility)
add_custom_command(TARGET ZFFramework_test PRE_BUILD COMMAND
    ${ZF_COPY_RES} ${ZF_ROOT_PATH}/_release/AndroidStudio/module/ZFUIKit/src/main/assets ${PROJECT_SOURCE_DIR}/src/main/assets)
add_library(ZFUIKit SHARED IMPORTED)
set_target_properties(ZFUIKit PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZFUIKit.so)
target_link_libraries(ZFFramework_test ZFUIKit)
add_custom_command(TARGET ZFFramework_test PRE_BUILD COMMAND
    ${ZF_COPY_RES} ${ZF_ROOT_PATH}/_release/AndroidStudio/module/ZFAddition/src/main/assets ${PROJECT_SOURCE_DIR}/src/main/assets)
add_library(ZFAddition SHARED IMPORTED)
set_target_properties(ZFAddition PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZFAddition.so)
target_link_libraries(ZFFramework_test ZFAddition)
add_custom_command(TARGET ZFFramework_test PRE_BUILD COMMAND
    ${ZF_COPY_RES} ${ZF_ROOT_PATH}/_release/AndroidStudio/module/ZFUIWidget/src/main/assets ${PROJECT_SOURCE_DIR}/src/main/assets)
add_library(ZFUIWidget SHARED IMPORTED)
set_target_properties(ZFUIWidget PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZFUIWidget.so)
target_link_libraries(ZFFramework_test ZFUIWidget)
add_custom_command(TARGET ZFFramework_test PRE_BUILD COMMAND
    ${ZF_COPY_RES} ${ZF_ROOT_PATH}/_release/AndroidStudio/module/ZFLua/src/main/assets ${PROJECT_SOURCE_DIR}/src/main/assets)
add_library(ZFLua SHARED IMPORTED)
set_target_properties(ZFLua PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZFLua.so)
target_link_libraries(ZFFramework_test ZFLua)
add_custom_command(TARGET ZFFramework_test PRE_BUILD COMMAND
    ${ZF_COPY_RES} ${ZF_ROOT_PATH}/_release/AndroidStudio/module/ZFUIWebKit/src/main/assets ${PROJECT_SOURCE_DIR}/src/main/assets)
add_library(ZFUIWebKit SHARED IMPORTED)
set_target_properties(ZFUIWebKit PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZFUIWebKit.so)
target_link_libraries(ZFFramework_test ZFUIWebKit)
add_custom_command(TARGET ZFFramework_test PRE_BUILD COMMAND
    ${ZF_COPY_RES} ${ZF_ROOT_PATH}/_release/AndroidStudio/module/ZF_impl/src/main/assets ${PROJECT_SOURCE_DIR}/src/main/assets)
add_library(ZF_impl SHARED IMPORTED)
set_target_properties(ZF_impl PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZF_impl.so)
target_link_libraries(ZFFramework_test ZF_impl)
add_custom_command(TARGET ZFFramework_test PRE_BUILD COMMAND
    ${ZF_COPY_RES} ${ZF_ROOT_PATH}/_release/AndroidStudio/module/ZF_loader_impl/src/main/assets ${PROJECT_SOURCE_DIR}/src/main/assets)
add_library(ZF_loader_impl SHARED IMPORTED)
set_target_properties(ZF_loader_impl PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZF_loader_impl.so)
target_link_libraries(ZFFramework_test ZF_loader_impl)
add_custom_command(TARGET ZFFramework_test PRE_BUILD COMMAND
    ${ZF_COPY_RES} ${ZF_ROOT_PATH}/_release/AndroidStudio/module/ZFCore_impl/src/main/assets ${PROJECT_SOURCE_DIR}/src/main/assets)
add_library(ZFCore_impl SHARED IMPORTED)
set_target_properties(ZFCore_impl PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZFCore_impl.so)
target_link_libraries(ZFFramework_test ZFCore_impl)
add_custom_command(TARGET ZFFramework_test PRE_BUILD COMMAND
    ${ZF_COPY_RES} ${ZF_ROOT_PATH}/_release/AndroidStudio/module/ZFAlgorithm_impl/src/main/assets ${PROJECT_SOURCE_DIR}/src/main/assets)
add_library(ZFAlgorithm_impl SHARED IMPORTED)
set_target_properties(ZFAlgorithm_impl PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZFAlgorithm_impl.so)
target_link_libraries(ZFFramework_test ZFAlgorithm_impl)
add_custom_command(TARGET ZFFramework_test PRE_BUILD COMMAND
    ${ZF_COPY_RES} ${ZF_ROOT_PATH}/_release/AndroidStudio/module/ZFUIKit_impl/src/main/assets ${PROJECT_SOURCE_DIR}/src/main/assets)
add_library(ZFUIKit_impl SHARED IMPORTED)
set_target_properties(ZFUIKit_impl PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZFUIKit_impl.so)
target_link_libraries(ZFFramework_test ZFUIKit_impl)
add_custom_command(TARGET ZFFramework_test PRE_BUILD COMMAND
    ${ZF_COPY_RES} ${ZF_ROOT_PATH}/_release/AndroidStudio/module/ZFLua_impl/src/main/assets ${PROJECT_SOURCE_DIR}/src/main/assets)
add_library(ZFLua_impl SHARED IMPORTED)
set_target_properties(ZFLua_impl PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZFLua_impl.so)
target_link_libraries(ZFFramework_test ZFLua_impl)
add_custom_command(TARGET ZFFramework_test PRE_BUILD COMMAND
    ${ZF_COPY_RES} ${ZF_ROOT_PATH}/_release/AndroidStudio/module/ZFUIWebKit_impl/src/main/assets ${PROJECT_SOURCE_DIR}/src/main/assets)
add_library(ZFUIWebKit_impl SHARED IMPORTED)
set_target_properties(ZFUIWebKit_impl PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/libZFUIWebKit_impl.so)
target_link_libraries(ZFFramework_test ZFUIWebKit_impl)

