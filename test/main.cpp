#include <cppunit/ui/text/TestRunner.h>
#include "ScalingUpTest.cpp"

int main( int argc, char **argv)
{
  CppUnit::TextUi::TestRunner runner;
  //runner.addTest( ScalingUpTest );
  runner.run();
  return 0;
}
