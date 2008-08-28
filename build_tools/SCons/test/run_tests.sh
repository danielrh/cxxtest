#!/bin/bash
function test() {
if [[ -d "$1" ]]
then
    echo "### RUNNING TEST $1 ###"
    cd "$1"
    scons --clean && scons . && scons check
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
test default_env &&\
test nonstandard_cxxtest_dir &&\
test need_cpppath
