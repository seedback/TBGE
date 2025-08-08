#!/bin/bash

CLEAN=0
TEST=0
RUN=0
INIT=0
HELP=0
DEBUG=0
DOC=0
RELEASE=0
TARGET=""
TESTTARGET=""
OPTION_COUNT=0

for arg in "$@"; do
  case "$arg" in
    -c|--clean|--clear)
      CLEAN=1
      ;;
    -t|--test)
      TEST=1
      ;;
    -r|--run)
      RUN=1
      ;;
    -i|--init)
      INIT=1
      ;;
    -h|-\?|--help)
      HELP=1
      ;;
    -d|--debug)
      DEBUG=1
      ;;
    --doc)
      DOC=1
      ;;
    --release)
      RELEASE=1
      ;;
    --target=*)
      TARGET="${arg#*=}"
      ;;
    --test-target=*)
      TESTTARGET="${arg#*=}"
      ;;
    *)
      echo "Unknown argument: $arg" >&2
      exit 1
      ;;
  esac
done

if [[ $TEST -eq 1 ]]; then
  DEBUG=1;
fi

echo "CLEAN=$CLEAN"
echo "TEST=$TEST"
echo "RUN=$RUN"
echo "INIT=$INIT"
echo "HELP=$HELP"
echo "DEBUG=$DEBUG"
echo "RELEASE=$RELEASE"
echo "TARGET=$TARGET"

BAZEL_FLAGS=""
if [[ $DEBUG -eq 1 ]]; then
  BAZEL_FLAGS+=" --config=debug"
elif [[ $TEST -eq 1 ]]; then
  BAZEL_FLAGS+=" --config=test"
elif [[ $RELEASE -eq 1 ]]; then
  BAZEL_FLAGS+=" --config=release"
fi

if [[ $CLEAN -eq 1 ]]; then
  bazel clean
fi

if [[ $HELP -eq 1 ]]; then
  cat <<EOF
Builds the current project.
Usage:
  ./build.sh [options]
Options:
  -h, -?, --help      Show this help message and exit.
  -t, --test          Run tests.
  -r, --run           Run the main target.
  -d, --debug         Build in debug mode.
  --release           Build in release mode.
  --target=TARGET     Specify a custom Bazel target (default: //:tbge_main, or //:tbge_test with --test).
Description:
  This script automates the build process for the project.
EOF
  exit 0
fi

if [[ $DOC -eq 1 ]]; then
  ./docs.sh
fi

if [[ $INIT -eq 1 ]]; then
  TESTTARGET="tbge_init"
  TARGET="tbge_init"
fi

if [[ $TEST -eq 1 ]]; then
  [[ -z "$TESTTARGET" ]] && TESTTARGET="tbge_test"
  bazel test $BAZEL_FLAGS //:"$TESTTARGET"
fi

if [[ $RUN -eq 1 ]]; then
  [[ -z "$TARGET" ]] && TARGET="tbge_main"
  bazel run $BAZEL_FLAGS //:"$TARGET"
fi

if [[ $RUN -eq 0 && $TEST -eq 0 ]]; then
  [[ -z "$TARGET" ]] && TARGET="tbge_main"
  bazel build $BAZEL_FLAGS //:"$TARGET"
fi

exit $?