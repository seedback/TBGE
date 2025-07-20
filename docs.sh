#!/bin/bash

CLEAN=0
OPEN=0
HELP=0

for arg in "$@"; do
  case "$arg" in
    -c|--clean) CLEAN=1 ;;
    -o|--open) OPEN=1 ;;
    -h|--help|-\?) HELP=1 ;;
  esac
done

if [[ $HELP -eq 1 ]]; then
  echo "Usage: $0 [options]"
  echo "Options:"
  echo "  -h, --help      Show this help message"
  echo "  -c, --clean     Remove the docs/ directory before building"
  echo "  -o, --open      Open the generated HTML documentation"
  exit 0
fi

if [[ $CLEAN -eq 1 ]]; then
  echo "Cleaning docs"
  rm -rf docs/
fi

doxygen Doxyfile

if [[ $OPEN -eq 1 ]]; then
  echo "Opening HTML"
  start docs/html/index.html
fi