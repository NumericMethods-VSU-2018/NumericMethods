#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "parser.h"

class ParserTest : public CppUnit::TestFixture
{
public:
    CPPUNIT_TEST_SUITE(ParserTest);
    CPPUNIT_TEST(parseInput1);
    CPPUNIT_TEST(parseInput2);
    CPPUNIT_TEST_SUITE_END();

protected:
    void parseInput1();
    void parseInput2();

private:
    InputData testInput(const std::string& input,
            size_t Nx, size_t Ny,
            std::vector<CoordDiff> hx,
            std::vector<CoordDiff> hy,
            Coord x0, Coord y0);
};
