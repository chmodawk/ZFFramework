#!bash

WORK_DIR=$(cd "$(dirname "$0")"; pwd)
iOS_SRCROOT=$1
iOS_CONFIGURATION_BUILD_DIR=$2
iOS_CONTENTS_FOLDER_PATH=$3
if test "x-$iOS_SRCROOT" = "x-" || test "x-$iOS_CONFIGURATION_BUILD_DIR" = "x-" || test "x-$iOS_CONFIGURATION_BUILD_DIR" = "x-" ; then
    echo usage:
    echo   ZFCopyResource.sh SRCROOT CONFIGURATION_BUILD_DIR CONTENTS_FOLDER_PATH
    exit 1
fi

ZF_ROOT_PATH=${iOS_SRCROOT}/../../../../../ZFFramework
ZF_TOOLS_PATH=$ZF_ROOT_PATH/tools
RES_DST_PATH=${iOS_CONFIGURATION_BUILD_DIR}/${iOS_CONTENTS_FOLDER_PATH}/zfres

sh "$ZF_TOOLS_PATH/common/copy_res.sh" "$ZF_ROOT_PATH/ZF/ZFCore/zfres" "$RES_DST_PATH"
sh "$ZF_TOOLS_PATH/common/copy_res.sh" "$ZF_ROOT_PATH/ZF/ZFAlgorithm/zfres" "$RES_DST_PATH"
sh "$ZF_TOOLS_PATH/common/copy_res.sh" "$ZF_ROOT_PATH/ZF/ZFUtility/zfres" "$RES_DST_PATH"
sh "$ZF_TOOLS_PATH/common/copy_res.sh" "$ZF_ROOT_PATH/ZF/ZFUIKit/zfres" "$RES_DST_PATH"
sh "$ZF_TOOLS_PATH/common/copy_res.sh" "$ZF_ROOT_PATH/ZF/ZFAddition/zfres" "$RES_DST_PATH"
sh "$ZF_TOOLS_PATH/common/copy_res.sh" "$ZF_ROOT_PATH/ZF/ZFUIWidget/zfres" "$RES_DST_PATH"
sh "$ZF_TOOLS_PATH/common/copy_res.sh" "$ZF_ROOT_PATH/ZF/ZF_impl/zfres" "$RES_DST_PATH"
sh "$ZF_TOOLS_PATH/common/copy_res.sh" "$ZF_ROOT_PATH/ZF/ZF_loader_impl/zfres" "$RES_DST_PATH"
sh "$ZF_TOOLS_PATH/common/copy_res.sh" "$ZF_ROOT_PATH/ZF/ZFCore_impl/zfres" "$RES_DST_PATH"
sh "$ZF_TOOLS_PATH/common/copy_res.sh" "$ZF_ROOT_PATH/ZF/ZFAlgorithm_impl/zfres" "$RES_DST_PATH"
sh "$ZF_TOOLS_PATH/common/copy_res.sh" "$ZF_ROOT_PATH/ZF/ZFUIKit_impl/zfres" "$RES_DST_PATH"

sh "$ZF_TOOLS_PATH/common/copy_res.sh" "${iOS_SRCROOT}/../../../zfres" "$RES_DST_PATH"

