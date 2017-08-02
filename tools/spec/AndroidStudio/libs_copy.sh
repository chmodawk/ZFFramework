#!bash

WORK_DIR=$(cd "$(dirname "$0")"; pwd)
PROJ_NAME=$1
PROJ_PATH=$2
if test "x-$PROJ_NAME" = "x-" || test "x-$PROJ_PATH" = "x-" ; then
    echo usage:
    echo   libs_copy.sh PROJ_NAME PROJ_PATH
    exit 1
fi

ZF_ROOT_PATH=$WORK_DIR/../../..

mkdir -p "$ZF_ROOT_PATH/_release/AndroidStudio/module/$PROJ_NAME/libs/libs" >/dev/null 2>&1
cp -rf "$PROJ_PATH/build/intermediates/bundles/default/jni/." "$ZF_ROOT_PATH/_release/AndroidStudio/module/$PROJ_NAME/libs/libs/" >/dev/null 2>&1
sh "$ZF_ROOT_PATH/tools/common/copy_header.sh" "$PROJ_PATH/../../../zfsrc" "$ZF_ROOT_PATH/_release/AndroidStudio/module/$PROJ_NAME/libs/include" >/dev/null 2>&1

JAR_FILE_SIZE=`du -b "$PROJ_PATH/build/intermediates/bundles/default/classes.jar" | awk '{print $1}'`
if test $JAR_FILE_SIZE -ge 1024 ; then
    cp "$PROJ_PATH/build/intermediates/bundles/default/classes.jar" "$ZF_ROOT_PATH/_release/AndroidStudio/module/$PROJ_NAME/libs/$PROJ_NAME.jar" >/dev/null 2>&1
fi

sh "$ZF_ROOT_PATH/tools/common/copy_res.sh" "$PROJ_PATH/../../../zfres" "$ZF_ROOT_PATH/_release/AndroidStudio/module/$PROJ_NAME/src/main/assets/zfres" >/dev/null 2>&1

sh "$ZF_ROOT_PATH/tools/common/copy_check.sh" "$ZF_ROOT_PATH/_release/AndroidStudio/module/$PROJ_NAME" "$ZF_ROOT_PATH/_release/AndroidStudio/all" >/dev/null 2>&1

exit 0

