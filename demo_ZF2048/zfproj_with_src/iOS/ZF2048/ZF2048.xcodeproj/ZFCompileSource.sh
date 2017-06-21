#!bash

WORK_DIR=$(cd "$(dirname "$0")"; pwd)
iOS_SRCROOT=$1
iOS_CONFIGURATION_BUILD_DIR=$2
iOS_CONTENTS_FOLDER_PATH=$3
if test "x-$iOS_SRCROOT" = "x-" || test "x-$iOS_CONFIGURATION_BUILD_DIR" = "x-" || test "x-$iOS_CONFIGURATION_BUILD_DIR" = "x-" ; then
    echo usage:
    echo   ZFCompileSource.sh SRCROOT CONFIGURATION_BUILD_DIR CONTENTS_FOLDER_PATH
    exit 1
fi

ZF_ROOT_PATH=${iOS_SRCROOT}/../../../../../ZFFramework
ZF_TOOLS_PATH=$ZF_ROOT_PATH/tools
COMPILE_DST_PATH=${iOS_SRCROOT}/ProjectFiles

sh $ZF_TOOLS_PATH/common/unity_build.sh "${COMPILE_DST_PATH}/zfgensrc_ZF2048.mm" "${iOS_SRCROOT}/../../../zfsrc"
sh $ZF_TOOLS_PATH/common/unity_build.sh "${COMPILE_DST_PATH}/zfgensrc_ZFCore.mm" "$ZF_ROOT_PATH/ZF/ZFCore/zfsrc"
sh $ZF_TOOLS_PATH/common/unity_build.sh "${COMPILE_DST_PATH}/zfgensrc_ZFAlgorithm.mm" "$ZF_ROOT_PATH/ZF/ZFAlgorithm/zfsrc"
sh $ZF_TOOLS_PATH/common/unity_build.sh "${COMPILE_DST_PATH}/zfgensrc_ZFUtility.mm" "$ZF_ROOT_PATH/ZF/ZFUtility/zfsrc"
sh $ZF_TOOLS_PATH/common/unity_build.sh "${COMPILE_DST_PATH}/zfgensrc_ZFUIKit.mm" "$ZF_ROOT_PATH/ZF/ZFUIKit/zfsrc"
sh $ZF_TOOLS_PATH/common/unity_build.sh "${COMPILE_DST_PATH}/zfgensrc_ZFAddition.mm" "$ZF_ROOT_PATH/ZF/ZFAddition/zfsrc"
sh $ZF_TOOLS_PATH/common/unity_build.sh "${COMPILE_DST_PATH}/zfgensrc_ZFUIWidget.mm" "$ZF_ROOT_PATH/ZF/ZFUIWidget/zfsrc"
sh $ZF_TOOLS_PATH/common/unity_build.sh "${COMPILE_DST_PATH}/zfgensrc_ZF_impl.mm" "$ZF_ROOT_PATH/ZF/ZF_impl/zfsrc"
sh $ZF_TOOLS_PATH/common/unity_build.sh "${COMPILE_DST_PATH}/zfgensrc_ZF_loader_impl.mm" "$ZF_ROOT_PATH/ZF/ZF_loader_impl/zfsrc"
sh $ZF_TOOLS_PATH/common/unity_build.sh "${COMPILE_DST_PATH}/zfgensrc_ZFCore_impl.mm" "$ZF_ROOT_PATH/ZF/ZFCore_impl/zfsrc"
sh $ZF_TOOLS_PATH/common/unity_build.sh "${COMPILE_DST_PATH}/zfgensrc_ZFAlgorithm_impl.mm" "$ZF_ROOT_PATH/ZF/ZFAlgorithm_impl/zfsrc"
sh $ZF_TOOLS_PATH/common/unity_build.sh "${COMPILE_DST_PATH}/zfgensrc_ZFUIKit_impl.mm" "$ZF_ROOT_PATH/ZF/ZFUIKit_impl/zfsrc"


