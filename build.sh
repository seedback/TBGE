#!/bin/bash

TEST=0
RUN=0
HELP=0
TARGET=""
OPTION_COUNT=0

for arg in "$@"; do
  case "$arg" in
    -t|--test) TEST=1; OPTION_COUNT=$((OPTION_COUNT+1)) ;;
    -r|--run) RUN=1; OPTION_COUNT=$((OPTION_COUNT+1)) ;;
    -h|-?|--help) HELP=1; OPTION_COUNT=$((OPTION_COUNT+1)) ;;
    --target=*)
      TARGET="${arg#*=}"
      ;;
  esac
done

if [[ $OPTION_COUNT -gt 1 ]]; then
  echo "Error: Only one of -t/--test, -r/--run, or -h/--help can be used at a time." >&2
  exit 1
fi

if [[ $HELP -eq 1 ]]; then
  echo "Builds the current project."
  echo "Usage:"
  echo "  ./build.sh [options]"
  echo "Options:"
  echo "  -h, -?, --help      Show this help message and exit."
  echo "  -t, --test          Run tests."
  echo "  -r, --run           Run the main target."
  echo "  --target=TARGET     Specify a custom Bazel target (default: //:tbge_main, or //:tbge_test with --test)."
  echo "Description:"
  echo "  This script automates the build process for the project."
  echo "  Except for --target, only one option can be used at a time."
  exit 1
elif [[ $TEST -eq 1 ]]; then
  if [[ -z "$TARGET" ]]; then
    TARGET="tbge_test"
  fi
  bazel test --cxxopt=/std:c++20 --test_output=all //:"$TARGET"
  exit 1
elif [[ $RUN -eq 1 ]]; then
  if [[ -z "$TARGET" ]]; then
    TARGET="tbge_main"
  fi
  bazel run --cxxopt=/std:c++20 //:"$TARGET"
  exit 1
else
  if [[ -z "$TARGET" ]]; then
    TARGET="tbge_main"
  fi
  bazel build --cxxopt=/std:c++20 //:"$TARGET"
  exit 1
fi
