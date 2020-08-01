#!/bin/bash

ROOT_DIR=$(cd $(dirname $0)../; pwd)
TEST_DIR=${ROOT_DIR}/test
BUILD_DIR=${ROOT_DIR}/build

echo $ROOT_DIR

function clean {
  echo "--- clean ---"
  rm -rf $BUILD_DIR 2> /dev/null
}

function build {
  echo "--- build ---"
  mkdir $BUILD_DIR && cd $BUILD_DIR
  cmake .. -DBUILD_TYPE=release -DCMAKE_EXPORT_COMPILE_COMMANDS=1
  rc -J ${BUILD_DIR}/compile_commands.json
  make
  if [ ! $? -eq 0 ]; then
    echo "[Error] build failed"
    exit 1
  fi
}

function run {
  ${BUILD_DIR}/src/main.out
}

clean
build
run

