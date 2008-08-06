/* Generated file, do not edit */

// -*- C++ -*-
#define CXXTEST_ABORT_TEST_ON_FAIL
#ifndef CXXTEST_HAVE_EH
#define CXXTEST_HAVE_EH
#endif
#define CXXTEST_RUNNING

#include <cxxtest/TestListener.h>
#include <cxxtest/CountingTracker.h>
#include <cxxtest/TestRunner.h>

#include <cxxtest/ErrorPrinter.h>

int main()
{
    return CxxTest::ErrorPrinter().run();
}

// The CxxTest "world"
#include "ThrowNoStd.h"

static ThrowNoStd suite_ThrowNoStd;

class TestDescriptionBase_ThrowNoStd : public CxxTest::TestDescription {
public:
 const char *file() const { return "ThrowNoStd.h"; }
 const char *suiteName() const { return "ThrowNoStd"; }
};

static class TestDescription_ThrowNoStd_testThrowNoStd : public TestDescriptionBase_ThrowNoStd {
public:
 unsigned line() const { return 6; }
 const char *testName() const { return "testThrowNoStd"; }
 void run() const { suite_ThrowNoStd.testThrowNoStd(); }
} testDescription_ThrowNoStd_testThrowNoStd;

static const CxxTest::TestDescription *testDescriptions_ThrowNoStd[] = {
 { &testDescription_ThrowNoStd_testThrowNoStd },
 { &CxxTest::TestDescription::_dummy }
};

static class SuiteDescription_ThrowNoStd : public CxxTest::SuiteDescription {
public:
 const char *file() const { return "ThrowNoStd.h"; }
 unsigned line() const { return 3; }
 const char *suiteName() const { return "ThrowNoStd"; }
 unsigned numTests() const { return 1; }
 CxxTest::TestSuite *suite() const { return &suite_ThrowNoStd; }
 const CxxTest::TestDescription &testDescription( unsigned i ) const { return *(testDescriptions_ThrowNoStd[i]); }
} suiteDescription_ThrowNoStd;

static const CxxTest::SuiteDescription *suiteDescriptions_TheWorld[] = {
 { &suiteDescription_ThrowNoStd },
 { &CxxTest::SuiteDescription::_dummy }
};

static class WorldDescription_TheWorld : public CxxTest::WorldDescription {
public:
 unsigned numSuites() const { return 1; }
 unsigned numTotalTests() const { return 1; }
 const CxxTest::SuiteDescription &suiteDescription( unsigned i ) const
  { return *(suiteDescriptions_TheWorld[i]); }
protected:
 void setUp() const {
 }
 void tearDown() const {
 }
} worldDescription_theWorld;

CxxTest::TestListener CxxTest::TestListener::_dummy;
CxxTest::TestTracker CxxTest::TestTracker::_dummy;
const CxxTest::WorldDescription CxxTest::WorldDescription::_dummy;
const CxxTest::SuiteDescription CxxTest::SuiteDescription::_dummy;
const CxxTest::TestDescription CxxTest::TestDescription::_dummy;
CxxTest::TestTracker *CxxTest::TestTracker::_tracker = &CxxTest::TestTracker::_dummy;
CxxTest::TestListener *CxxTest::TestListener::_listener = &CxxTest::TestListener::_dummy;

CxxTest::CountingTracker CxxTest::TestRunner::_counter;
const CxxTest::WorldDescription &CxxTest::TestRunner::_world = worldDescription_theWorld;


