#!/bin/bash
function test() {
    if [[ "x$SELECT_TEST" != "x" ]]
    then
        if [[ "x${1%'/'}" != "x$SELECT_TEST" ]]
        then
            return 0
        fi
    fi

    if [[ -d "$1" ]]
    then
        echo "### RUNNING TEST $1 ###"
        cd "$1"
        scons --clean && scons . && scons check && scons --clean
        ret=$?
        if [[ "x$ret" = "x0" ]]
        then
            echo "### TEST $1 SUCCESSFUL ###"
            echo
        else
            echo "### TEST $1 FAILED ###"
            echo
        fi
        cd ..
        return $ret
    else
        echo "Cannot find test!"
        return 1
    fi
}

function cleanup() {
    rm */.sconsign.dblite
}

SELECT_TEST=""
if [[ -d "$1" ]] || [[ "x" == "x$1" ]]
then
    SELECT_TEST=${1%'/'}
else
    cat <<USAGE
This is the test runner for the SCons builder unit tests.

Usage: run_tests.sh [directory]
If the directory is provided, this will only run the test in that directory.
Otherwise, it will run all the tests.
USAGE
    exit 2
fi

test "default_env" &&\
test "nonstandard_cxxtest_dir" &&\
test "need_cpppath" &&\
test "string_cpppath" &&\
test "printer_propagation" &&\
cleanup
