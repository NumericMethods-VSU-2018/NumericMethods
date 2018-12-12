#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include "BandMatrixTest.h"
#include "ReorderTest.h"

int main( int argc, char **argv)
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(BandMatrixTest::suite());
  runner.addTest(ReorderTest::suite());
  runner.run();
  return 0;
}