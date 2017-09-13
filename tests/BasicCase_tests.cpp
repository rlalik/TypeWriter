/*
 * Copyright (c) 2017 Rafal Lalik rafallalik@gmail.com
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <cppunit/extensions/HelperMacros.h>

#include <typewriter.h>

class BasicCase_tests : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( BasicCase_tests );
	CPPUNIT_TEST( TestErasing );
    CPPUNIT_TEST( TestDoubleErasing );
    CPPUNIT_TEST( TestFrameSkip );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();

protected:
	void TestErasing();
    void TestDoubleErasing();
    void TestFrameSkip();
};

CPPUNIT_TEST_SUITE_REGISTRATION( BasicCase_tests );

void BasicCase_tests::setUp()
{
}

void BasicCase_tests::TestErasing()
{
	TypeWriter tw;
    tw.setPattern("a,b,,c,<");
    CPPUNIT_ASSERT_EQUAL(4, tw.parse());
    CPPUNIT_ASSERT_EQUAL(std::string("a"), tw.render(0));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(1));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(2));
    CPPUNIT_ASSERT_EQUAL(std::string("abc"), tw.render(3));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(4));
}

void BasicCase_tests::TestDoubleErasing()
{
	TypeWriter tw;
    tw.setPattern("a,b,,c,<<");
    CPPUNIT_ASSERT_EQUAL(4, tw.parse());
    CPPUNIT_ASSERT_EQUAL(std::string("a"), tw.render(0));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(1));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(2));
    CPPUNIT_ASSERT_EQUAL(std::string("abc"), tw.render(3));
    CPPUNIT_ASSERT_EQUAL(std::string("a"), tw.render(4));

    tw.setPattern("a,b,,c,<<de");
    CPPUNIT_ASSERT_EQUAL(4, tw.parse());
    CPPUNIT_ASSERT_EQUAL(std::string("a"), tw.render(0));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(1));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(2));
    CPPUNIT_ASSERT_EQUAL(std::string("abc"), tw.render(3));
    CPPUNIT_ASSERT_EQUAL(std::string("ade"), tw.render(4));
}

void BasicCase_tests::TestFrameSkip()
{
	TypeWriter tw;
    tw.setPattern("a,b,[4]c,<<d");
    CPPUNIT_ASSERT_EQUAL(6, tw.parse());
    CPPUNIT_ASSERT_EQUAL(std::string("a"), tw.render(0));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(1));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(2));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(3));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(4));
    CPPUNIT_ASSERT_EQUAL(std::string("abc"), tw.render(5));
    CPPUNIT_ASSERT_EQUAL(std::string("ad"), tw.render(6));

    tw.setPattern("e,f,[4f]g,<<h");
    CPPUNIT_ASSERT_EQUAL(6, tw.parse());
    CPPUNIT_ASSERT_EQUAL(std::string("e"), tw.render(0));
    CPPUNIT_ASSERT_EQUAL(std::string("ef"), tw.render(1));
    CPPUNIT_ASSERT_EQUAL(std::string("ef"), tw.render(2));
    CPPUNIT_ASSERT_EQUAL(std::string("ef"), tw.render(3));
    CPPUNIT_ASSERT_EQUAL(std::string("ef"), tw.render(4));
    CPPUNIT_ASSERT_EQUAL(std::string("efg"), tw.render(5));
    CPPUNIT_ASSERT_EQUAL(std::string("eh"), tw.render(6));

    tw.setPattern("i,j,[4s]k,<<l");
    CPPUNIT_ASSERT_EQUAL(102, tw.parse());
    CPPUNIT_ASSERT_EQUAL(std::string("i"), tw.render(0));
    CPPUNIT_ASSERT_EQUAL(std::string("ij"), tw.render(1));
    CPPUNIT_ASSERT_EQUAL(std::string("ij"), tw.render(1 + 4*tw.getFrameRate()-1));
    CPPUNIT_ASSERT_EQUAL(std::string("ijk"), tw.render(1 + 4*tw.getFrameRate()));
    CPPUNIT_ASSERT_EQUAL(std::string("il"), tw.render(1 + 4*tw.getFrameRate()+1));

    tw.setPattern("m,n,[4g]o,<<p");
    CPPUNIT_ASSERT_EQUAL(-7, tw.parse());
}
