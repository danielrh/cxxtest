#ifndef __cxxtest__TestSuite_cpp__
#define __cxxtest__TestSuite_cpp__

#include <sstream>
#include <fstream>
#include <cxxtest/TestSuite.h>

namespace CxxTest
{
    //
    // TestSuite members
    //
    TestSuite::~TestSuite() {}
    void TestSuite::setUp() {}
    void TestSuite::tearDown() {}

    //
    // Test-aborting stuff
    //
    static bool currentAbortTestOnFail = false;

    bool abortTestOnFail()
    {
        return currentAbortTestOnFail;
    }

    void setAbortTestOnFail( bool value )
    {
        currentAbortTestOnFail = value;
    }
    
    void doAbortTest()
    {
#   if defined(_CXXTEST_HAVE_EH)
        if ( currentAbortTestOnFail )
            throw AbortTest();
#   endif // _CXXTEST_HAVE_EH
    }

    //
    // Max dump size
    //
    static unsigned currentMaxDumpSize = CXXTEST_MAX_DUMP_SIZE;

    unsigned maxDumpSize()
    {
        return currentMaxDumpSize;
    }
    
    void setMaxDumpSize( unsigned value )
    {
        currentMaxDumpSize = value;
    }

    //
    // Some non-template functions
    //
    void doTrace( const char *file, unsigned line, const char *message )
    {
        if (tracker().print_tracing)
           tracker().trace( file, line, message );
    }

    void doWarn( const char *file, unsigned line, const char *message )
    {
        tracker().warning( file, line, message );
    }

    void doFailTest( const char *file, unsigned line, const char *message )
    {
        tracker().failedTest( file, line, message );
        TS_ABORT();
    }

    void doFailAssert( const char *file, unsigned line,
                       const char *expression, const char *message )
    {
        if ( message )
            tracker().failedTest( file, line, message );
        tracker().failedAssert( file, line, expression );
        TS_ABORT();
    }

    bool sameData( const void *x, const void *y, unsigned size )
    {
        if ( size == 0 )
            return true;
        
        if ( x == y )
            return true;

        if ( !x || !y )
            return false;

        const char *cx = (const char *)x;
        const char *cy = (const char *)y;
        while ( size -- )
            if ( *cx++ != *cy++ )
                return false;

        return true;
    }

    void doAssertSameData( const char *file, unsigned line,
                           const char *xExpr, const void *x,
                           const char *yExpr, const void *y,
                           const char *sizeExpr, unsigned size,
                           const char *message )
    {
        if ( !sameData( x, y, size ) ) {
            if ( message )
                tracker().failedTest( file, line, message );
            tracker().failedAssertSameData( file, line, xExpr, yExpr, sizeExpr, x, y, size );
            TS_ABORT();
        }
    }

    bool sameFiles( const char* file1, const char* file2, std::ostringstream& explanation)
    {
    std::string ppprev_line;
    std::string pprev_line;
    std::string prev_line;
    std::string curr_line;

    std::ifstream is1;
    is1.open(file1);
    std::ifstream is2;
    is2.open(file2);
    if (!is1) {
        explanation << "File '" << file1 << "' does not exist!";
        return false;
        }
    if (!is2) {
        explanation << "File '" << file2 << "' does not exist!";
        return false;
        }

    int nline=1;
    char c1, c2;
    while (1) {
        is1.get(c1);
        is2.get(c2);
        if (!is1 && !is2) return true;
        if (!is1) {
                explanation << "File '" << file1 << "' ended before file '" << file2 << "' (line " << nline << ")";
                explanation << std::endl << "= " << ppprev_line << std::endl << "=  " << pprev_line << std::endl << "= " << prev_line << std::endl << "< " << curr_line;
                is1.get(c1);
                while (is1 && (c1 != '\n')) {
                  explanation << c1;
                  is1.get(c1);
                  }
                explanation << std::endl;
                return false;
                }
        if (!is2) {
                explanation << "File '" << file2 << "' ended before file '" << file1 << "' (line " << nline << ")";
                explanation << std::endl << "= " << ppprev_line << std::endl << "=  " << pprev_line << std::endl << "= " << prev_line << std::endl << "> " << curr_line;
                is2.get(c2);
                while (is2 && (c2 != '\n')) {
                  explanation << c2;
                  is2.get(c2);
                  }
                explanation << std::endl;
                return false;
                }
        if (c1 != c2) {
                explanation << "Files '" << file1 << "' and '" << file2 << "' differ at line " << nline;
                explanation << std::endl << "= " << ppprev_line << std::endl << "=  " << pprev_line << std::endl << "= " << prev_line;

                explanation << std::endl << "< " << curr_line;
                is2.get(c1);
                while (is1 && (c1 != '\n')) {
                  explanation << c1;
                  is2.get(c1);
                  }
                explanation << std::endl;

                explanation << std::endl << "> " << curr_line;
                is2.get(c2);
                while (is2 && (c2 != '\n')) {
                  explanation << c2;
                  is2.get(c2);
                  }
                explanation << std::endl;

                return false;
                }
        if (c1 == '\n') {
           ppprev_line = pprev_line;
           pprev_line = prev_line;
           prev_line = curr_line;
           curr_line = "";
           nline++;
           }
        else {
           curr_line += c1;
           }
        }
    }

    void doAssertSameFiles( const char* file, unsigned line,
                            const char* file1, const char* file2,
                            const char* message)
    {
        std::ostringstream explanation;
        if ( !sameFiles( file1, file2, explanation ) ) {
            if ( message )
                tracker().failedTest( file, line, message );
            tracker().failedAssertSameFiles( file, line, file1, file2, explanation.str().c_str());
            TS_ABORT();
        }
    }

    void doFailAssertThrows( const char *file, unsigned line,
                             const char *expr, const char *type,
                             bool otherThrown,
                             const char *message )
    {
        if ( message )
            tracker().failedTest( file, line, message );
        
        tracker().failedAssertThrows( file, line, expr, type, otherThrown );
        TS_ABORT();
    }

    void doFailAssertThrowsNot( const char *file, unsigned line,
                                const char *expression, const char *message )
    {
        if ( message )
            tracker().failedTest( file, line, message );
        
        tracker().failedAssertThrowsNot( file, line, expression );
        TS_ABORT();
    }
}

#endif // __cxxtest__TestSuite_cpp__

// Copyright 2008 Sandia Corporation. Under the terms of Contract
// DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government
// retains certain rights in this software.

