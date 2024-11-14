#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
RESET='\033[0m'

main() {
    local command=$1

    if [ "$command" = "generate_one" ]; then
        generate_one $2
    fi
    if [ "$command" = "generate_all" ]; then
        generate_all
    fi
}

generate_all() {
    for test_file in $(ls tests | grep _test); do
        compile_and_run tests/$test_file
    done
    echo -e "${BLUE}Generating coverage report:${RESET} $test_file"
    lcov --capture --directory . --output-file coverage.info --include "*/dst/*" 1>/dev/null

    echo -e "${BLUE}Generating HTML report:${RESET} $test_file"
    genhtml coverage.info --output-directory tests_out/all 1>/dev/null

    rm *.gcda *.gcno coverage.info

    echo -e "${GREEN}URL:${RESET} file://$(pwd)/tests_out/all/index.html"
}

generate_one() {
    local dst=$1

    if [ -z "$dst" ]; then
        echo -e "${YELLOW}Usage:${RESET} ${GREEN}$0 generate_one <data_structure_to_test>${RESET}"
        exit 1
    fi

    test_file="tests/${dst}_test.cpp"

    if [ ! -f "$test_file" ]; then
        echo -e "${RED}File not found:${RESET} ${GREEN}$test_file${RESET}"
        exit 2
    fi

    compile_and_run $test_file

    echo -e "${BLUE}Generating coverage report:${RESET} $test_file"
    lcov --capture --directory . --output-file coverage.info --include "*/dst/*"

    echo -e "${BLUE}Generating HTML report:${RESET} $test_file"
    genhtml coverage.info --output-directory tests_out/$dst

    rm *.gcda *.gcno coverage.info # delete tmp files

    echo -e "${GREEN}URL:${RESET} file://$(pwd)/tests_out/${dst}/index.html"
}

compile_and_run() {
    local EXECUTION_FILE_NAME="tmp"
    local TEST_FILE=$1

    echo -e "${BLUE}Compiling test:${RESET} ${GREEN}$TEST_FILE${RESET}"
    g++ -fprofile-arcs -ftest-coverage -o $EXECUTION_FILE_NAME $TEST_FILE -lboost_unit_test_framework

    if [ ! $? -eq 0 ]; then 
        echo -e "${RED}Compilation failed${RESET}"
        exit 3
    fi

    echo -e "${BLUE}Running test:${RESET} ${GREEN}$TEST_FILE${RESET}"
    ./$EXECUTION_FILE_NAME
    rm $EXECUTION_FILE_NAME
}

main $1 $2
