#!/bin/bash

CLEAN=0
OPEN_HTML=0

for arg in "$@"; do
  case "$arg" in
    -c) CLEAN=1 ;;
    -h) OPEN_HTML=1 ;;
  esac
done

if [[ $CLEAN -eq 1 ]]; then
  echo "Cleaning docs"
  rm -rf docs/
fi

doxygen Doxyfile

if [[ $OPEN_HTML -eq 1 ]]; then
  echo "Opening HTML"
  start docs/html/index.html
fi