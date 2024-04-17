#!/bin/bash
usage() {
  echo "Usage: Add the flags --build and/or --run"
  exit 0
}

YELLOW='\e[33m'
DEFAULT='\e[39m'

if [ -z "$1" ]; then
  usage
fi

if [ $# -gt 2 ]; then
  echo "Too many arguments"
  usage
fi

if [[ ! "$@" =~ "--build" ]] && [[ ! "$@" =~ "--run" ]]; then
  echo "Flag not recognized"
  usage
fi

if [[ "$@" =~ "--build" ]]; then
  echo -e "${YELLOW}Building all tests...${DEFAULT}\n"
  cmake -S . -B build -DUNIT_TESTING=ON -DCMAKE_BUILD_TYPE=Debug && cmake --build build
fi

if [[ "$@" =~ "--run" ]]; then
  echo -e "\n${YELLOW}Running all tests...${DEFAULT}\n"
  ctest --test-dir build -V
fi
