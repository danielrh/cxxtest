# coding=UTF-8
# CxxTest builder by Gasper Azman
# Modified by J. Darby Mitchell (2008-08-22)
#
# please send bugreports/praise/comments/criticism to
# gasper.azman at gmail.com
#
# This has been somewhat inspired by my previous work here:
# http://www.scons.org/wiki/UnitTests
#
# This builder correctly tracks dependencies and supports just about every
# configuration option for CxxTest that I can think of. It automatically
# defines a target "check" (configurable), so all tests can be run with a
#   scons check
# This will first compile and then run the tests.
#
# The default configuration assumes that cxxtest is installed in the base
# source directory (where SConstruct is), that the cxxtestgen.py is under
# cxxtest/cxxtestgen.py and headers are in cxxtest/cxxtest/. The header
# include path is automatically added to CPPPATH.
#
# This should be in a file called cxxtest.py somewhere in the toolpath.
#
# CHANGELOG:
# 2008-08-28: Gašper Ažman Added CXXTEST_SKIP_ERRORS that makes all tests run no
#    matter whether they fail or succeed. Fixed the issue where CPPPATH would
#    vanish. Fixed bug #40
# 2008-08-25: Gasper Azman and Darby Mitchell (MIT) refactored the tool to
#    set defaults that don't override previously set environment variables, and 
#    automatically search for the cxxtestgen Python script in the path and 
#    project if it isn't specified by the user in the environment or kwargs.
# 2008-08-23: Gasper Azman removed Perl support, since SCons is based on Python
#    and CxxTest has plans to drop the cxxtestgen Perl script in the near future.
# 2008-03-29:
#    Fixed a bug introduced in the last version, where the script would fail if
#    CXXFLAGS was never set.
# 2008-03-23:
#    Added CXXTEST_CXXFLAGS_REMOVE
#    Bugfix: if only a single test was specified, scons check would do nothing
#    Bugfix: test would not compile if '#' was not a part of path. Now added
#    automatically.
# 2008-06-22:
#    Bugfix: on windows, the script would not work because windows does not
#    support running scripts without an explicit interpreter invocation
#    (./script.py). 
#    Patch kindly provided by Diego Nieto Cid (dnietoc at gmail dot com)
# 2008-06-25:
#    Bugfix: Diego also provided a patch to his added functionality, so that
#    now not all paths are imported, but just the path required to run the
#    interpreter.
#
# TODO:
#    [gasper] Make use of --root and --part, so that multifile tests are
#    feasable. Have to find a testcase (maybe diego).
#
# Last changed: 2008-06-26 10:35:l0 CEST

from SCons.Script import *
from SCons.Builder import Builder
from os import path

# A few warning classes created to notify users of problems
class ToolCxxTestWarning(SCons.Warnings.Warning):
    pass

SCons.Warnings.enableWarningClass(ToolCxxTestWarning)

def UnitTest(env, target, source = [], **kwargs):
    cxxflags = ""
    if (type(env["CXXFLAGS"]) == "str"):
        cxxflags = env["CXXFLAGS"]
    cxxflags = kwargs.get("CXXFLAGS", cxxflags)
    for item in env['CXXTEST_CXXFLAGS_REMOVE']:
        cxxflags = cxxflags.replace(item, "")
    kwargs["CXXFLAGS"] = cxxflags;
    test = env.Program(target, source = source, **kwargs)
    if (env['CXXTEST_SKIP_ERRORS']):
        runner = env.Action(test[0].abspath, exitstatfunc=lambda x:0)
    else:
        runner = env.Action(test[0].abspath)
    env.Alias(env['CXXTEST_TARGET'], test, runner)
    env.AlwaysBuild(env['CXXTEST_TARGET'])
    return test


def isValidScriptPath(cxxtestgen):
    """check keyword arg or environment variable locating cxxtestgen.py script"""
       
    if(cxxtestgen and cxxtestgen.endswith('.py') and path.exists(cxxtestgen) ):
        return True
    else:
        SCons.Warnings.warn(ToolCxxTestWarning,
                            "Invalid CXXTEST environment variable specified!")
        return False
    

def findCxxTestGen(env):
    """locate the cxxtestgen script by checking environment, path and project"""
    
    # check the SCons environment...
    # Then, check the OS environment...
    cxxtest = (env.get('CXXTEST', None) or
               os.environ.get('CXXTEST', None)
              )
    
    # If the user specified the location in the environment, make sure it was correct
    if(cxxtest and isValidScriptPath(cxxtest) ):
       return cxxtest
    
    # No valid environment variable found, so...
    # Next, check the path...
    # Finally, check the project
    cxxtest = (env.WhereIs('cxxtestgen.py') or 
               env.WhereIs('cxxtestgen.py', path=Dir(path.join('#', 'cxxtest') ).abspath) 
              )
    
    if(cxxtest):
        return cxxtest
    else:
        # If we weren't able to locate the cxxtestgen.py script, complain...
        SCons.Warnings.warn(
                ToolCxxTestWarning,
                "Unable to locate cxxtestgen in environment, path or project!")
        return None
    

def generate(env, **kwargs):
    """
    Accepted keyword arguments:
    CXXTEST         - the path to the cxxtestgen.py
                        Default: searches SCons environment, OS environment,
                        path and project in that order.
    CXXTEST_PRINTER - the printer to use.  Default: error-printer
    CXXTEST_OPTS    - other options to pass to cxxtest.  Default: ''
    CXXTEST_SUFFIX  - the suffix of the test files.  Default: '.t.h'
    CXXTEST_TARGET  - the target to append the tests to.  Default: check
    CXXTEST_CXXFLAGS_REMOVE - the flags that cxxtests can't compile with,
                              or give lots of warnings. Will be stripped.
                              Default: -pedantic -Weffc++
    CXXTEST_RUNNER  - the path to the python binary.
                        Default: searches path for python
    CXXTEST_SKIP_ERRORS - set to True to continue running the next test if one
                          test fails. Default: False
    ... and all others that Program() accepts, like CPPPATH etc.
    """

    print "Loading CxxTest tool..."
    
    #If the user specified the path to CXXTEST, make sure it is correct
    #otherwise, search for and set the default toolpath
    if(not kwargs.has_key('CXXTEST') or not isValidScriptPath(kwargs['CXXTEST']) ):
        env.SetDefault( CXXTEST = findCxxTestGen(env) )

    #
    # Expected behavior: keyword arguments override environment variables;
    # environment variables override default settings.
    #          
    env.SetDefault( CXXTEST_PRINTER = 'error-printer'       )
    env.SetDefault( CXXTEST_OPTS    = ''                    )
    env.SetDefault( CXXTEST_SUFFIX  = '.t.h'                )
    env.SetDefault( CXXTEST_TARGET  = 'check'               )
    env.SetDefault( CXXTEST_CPPPATH = ['#']                 )
    env.SetDefault( CXXTEST_RUNNER  = env.WhereIs('python') )
    env.SetDefault( CXXTEST_CXXFLAGS_REMOVE = ['-pedantic','-Weffc++'] )
    env.SetDefault( CXXTEST_SKIP_ERRORS = False             )
    
    #Here's where keyword arguments are applied
    apply(env.Replace, (), kwargs)
    
    cxxtest = env['CXXTEST']
    if(cxxtest):
        # Check to see if there is a 'cxxtest' subdirectory in the location where
        # the script was found.  If so, assume that is the header directory, and  
        # therefore the script directory should be included in the CPPPATH
        if(path.exists(path.join(path.dirname(cxxtest), 'cxxtest') ) ):
           # for some reason, setting PATH here doesn't work for me (Gašper)
           env.AppendUnique(CXXTEST_CPPPATH = [path.dirname(cxxtest)] )
        
        #
        # Create the Builder (only if we have a valid cxxtestgen!)
        #
        cxxtest_builder = Builder(
            action = "$CXXTEST_RUNNER $CXXTEST --$CXXTEST_PRINTER $CXXTEST_OPTS -o $TARGET $SOURCE",
            suffix = ".cpp",
            src_suffix = '$CXXTEST_SUFFIX'
            )

    def CxxTest(env, target, source = [], **kwargs):
        """Usage:
        The function is modelled to be called as the Program() call is:
        env.CxxTest('target_name') will build the test from the source
            target_name + env['CXXTEST_SUFFIX'],
        env.CxxTest('target_name', source = 'test_src.t.h') will build the test
            from test_src.t.h source,
        env.CxxTest('target_name, source = ['test_src.t.h', other_srcs]
            builds the test from source[0] and links in other files mentioned in
            sources,
        You may also add additional arguments to the function. In that case, they
        will be passed to the actual Program builder call unmodified. Convenient
        for passing different CPPPATHs and the sort. This function also appends
        CXXTEST_CPPPATH to CPPPATH. It does not clutter the environment's CPPPATH.
        """
        if (source == []):
            source = Split(target + env['CXXTEST_SUFFIX'])
        sources = Split(source)
        sources[0] = env.CxxTestCpp(sources[0], **kwargs)


        kwargs['CPPPATH'] = list(set(
            Split(kwargs.get('CPPPATH', [])) +
            Split(env.get(   'CPPPATH', [])) +
            Split(kwargs.get('CXXTEST_CPPPATH', [])) +
            Split(env.get(   'CXXTEST_CPPPATH', []))
            ))

        return UnitTest(env, target, source = sources, **kwargs)

    env.Append( BUILDERS = { "CxxTest" : CxxTest, "CxxTestCpp" : cxxtest_builder } )

def exists(env):
    return path.exists(env['CXXTEST'])
