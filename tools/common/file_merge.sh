#!bash

WORK_DIR=$(cd "$(dirname "$0")"; pwd)
FILE1_PATH=$1
FILE2_PATH=$2
DST_PATH=$3
if test "x-$FILE1_PATH" = "x-" || test "x-$FILE2_PATH" = "x-" || test "x-$DST_PATH" = "x-" ; then
    echo usage:
    echo   file_merge.sh FILE1_PATH FILE2_PATH DST_PATH
    exit 1
fi

cat "$FILE1_PATH" "$FILE2_PATH" > "$DST_PATH"

