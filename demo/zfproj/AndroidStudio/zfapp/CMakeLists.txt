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

function(ZFAddLib ZF_ROOT_PATH_ PROJ_NAME_ ZF_LIB_NAME_)
    add_library(${ZF_LIB_NAME_} SHARED IMPORTED)
    set_target_properties(${ZF_LIB_NAME_} PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH_}/_release/AndroidStudio/all/libs/libs/${ANDROID_ABI}/lib${ZF_LIB_NAME_}.so)
    target_link_libraries(${PROJ_NAME_} ${ZF_LIB_NAME_})
endfunction(ZFAddSrc)


ZFAddLib(${ZF_ROOT_PATH} ZFFramework_test ZFCore)
ZFAddLib(${ZF_ROOT_PATH} ZFFramework_test ZFAlgorithm)
ZFAddLib(${ZF_ROOT_PATH} ZFFramework_test ZFUtility)
ZFAddLib(${ZF_ROOT_PATH} ZFFramework_test ZFUIKit)
ZFAddLib(${ZF_ROOT_PATH} ZFFramework_test ZFAddition)
ZFAddLib(${ZF_ROOT_PATH} ZFFramework_test ZFUIWidget)
ZFAddLib(${ZF_ROOT_PATH} ZFFramework_test ZFLua)
ZFAddLib(${ZF_ROOT_PATH} ZFFramework_test ZFUIWebKit)

ZFAddLib(${ZF_ROOT_PATH} ZFFramework_test ZF_impl)
ZFAddLib(${ZF_ROOT_PATH} ZFFramework_test ZF_loader_impl)
ZFAddLib(${ZF_ROOT_PATH} ZFFramework_test ZFCore_impl)
ZFAddLib(${ZF_ROOT_PATH} ZFFramework_test ZFAlgorithm_impl)
ZFAddLib(${ZF_ROOT_PATH} ZFFramework_test ZFUIKit_impl)
ZFAddLib(${ZF_ROOT_PATH} ZFFramework_test ZFLua_impl)
ZFAddLib(${ZF_ROOT_PATH} ZFFramework_test ZFUIWebKit_impl)

