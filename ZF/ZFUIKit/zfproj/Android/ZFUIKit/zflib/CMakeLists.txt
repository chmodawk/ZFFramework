cmake_minimum_required(VERSION 3.4.1)

set(ZF_ROOT_PATH ${PROJECT_SOURCE_DIR}/../../../../../../../ZFFramework)

file(GLOB_RECURSE srcfiles RELATIVE ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/../../../../zfsrc/*.c
    ${PROJECT_SOURCE_DIR}/../../../../zfsrc/*.cpp
    ${PROJECT_SOURCE_DIR}/../../../../zfsrc_ext/*.c
    ${PROJECT_SOURCE_DIR}/../../../../zfsrc_ext/*.cpp
    )
add_library(ZFUIKit SHARED ${srcfiles})
set_target_properties(ZFUIKit PROPERTIES LINKER_LANGUAGE CXX)

find_library(log-lib log)
find_library(android-lib android)
target_link_libraries(ZFUIKit ${android-lib} ${log-lib})

include_directories(${PROJECT_SOURCE_DIR}/../../../../zfsrc)
include_directories(${ZF_ROOT_PATH}/_release/Android/all/libs/include)

function(ZFAddLib ZF_ROOT_PATH_ PROJ_NAME_ ZF_LIB_NAME_)
    add_library(${ZF_LIB_NAME_} SHARED IMPORTED)
    set_target_properties(${ZF_LIB_NAME_} PROPERTIES IMPORTED_LOCATION ${ZF_ROOT_PATH_}/_release/Android/all/libs/libs/${ANDROID_ABI}/lib${ZF_LIB_NAME_}.so)
    target_link_libraries(${PROJ_NAME_} ${ZF_LIB_NAME_})
endfunction(ZFAddSrc)


ZFAddLib(${ZF_ROOT_PATH} ZFUIKit ZFCore)
ZFAddLib(${ZF_ROOT_PATH} ZFUIKit ZFAlgorithm)
ZFAddLib(${ZF_ROOT_PATH} ZFUIKit ZFUtility)


