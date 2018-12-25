#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "ParserTest.h"

int main( int argc, char **argv)
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(ParserTest::suite());
  runner.run();
  return 0;
}
