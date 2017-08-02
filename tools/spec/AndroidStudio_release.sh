#!bash

WORK_DIR=$(cd "$(dirname "$0")"; pwd)
BUILD_TYPE=$1
PROJ_NAME=$2
PROJ_PATH=$3
if test "x-$BUILD_TYPE" = "x-" || test "x-$PROJ_NAME" = "x-" || test "x-$PROJ_PATH" = "x-" ; then
    echo usage:
    echo   AndroidStudio_release.sh BUILD_TYPE PROJ_NAME PROJ_PATH
    exit 1
fi

ZF_ROOT_PATH=$WORK_DIR/../..
ZF_TOOLS_PATH=$ZF_ROOT_PATH/tools

sh "$ZF_TOOLS_PATH/common/file_exist.sh" "$ZF_ROOT_PATH/_release/AndroidStudio/module/$PROJ_NAME/libs/libs" "*.so"
if test "$?" = "0" ; then
    exit 0
fi

_OLD_DIR=$(pwd)

cd "$PROJ_PATH/zfproj/AndroidStudio"
sh "gradlew" assembleRelease

cd "$_OLD_DIR"

