#!bash

WORK_DIR=$(cd "$(dirname "$0")"; pwd)
PROJ_PATH=$1
if test "x-$PROJ_PATH" = "x-" ; then
    echo usage:
    echo   unique_proj.sh PROJ_PATH
    exit 1
fi

ZF_ROOT_PATH=$WORK_DIR/../../..
ZF_TOOLS_PATH=$ZF_ROOT_PATH/tools

sh "$ZF_TOOLS_PATH/common/zfsh.sh" "$WORK_DIR/zf3rd/zfautoscript_zf3rd_setup_xUnique.zfsh"
python "$WORK_DIR/zf3rd/_repo/xUnique/xUnique.py" "$PROJ_PATH"

if test -e "$PROJ_PATH/project.pbxproj.ubak" ; then
    mv "$PROJ_PATH/project.pbxproj.ubak" "$PROJ_PATH/project.pbxproj"
fi

if test -e "$PROJ_PATH/project.pbxproj.sbak" ; then
    mv "$PROJ_PATH/project.pbxproj.sbak" "$PROJ_PATH/project.pbxproj"
fi

exit 0

