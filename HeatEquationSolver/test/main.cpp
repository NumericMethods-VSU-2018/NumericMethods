#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "SolverTest.h"

int main( int argc, char **argv)
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(SolverTest::suite());
  runner.run();
  return 0;
}
