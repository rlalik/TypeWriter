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
    tw.setRawString("a,b,,c,<");
    CPPUNIT_ASSERT_EQUAL(true, tw.parse());
    CPPUNIT_ASSERT_EQUAL(std::string("a"), tw.render(0));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(1));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(2));
    CPPUNIT_ASSERT_EQUAL(std::string("abc"), tw.render(3));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(4));
}

void BasicCase_tests::TestDoubleErasing()
{
	TypeWriter tw;
    tw.setRawString("a,b,,c,<<");
    CPPUNIT_ASSERT_EQUAL(true, tw.parse());
    CPPUNIT_ASSERT_EQUAL(std::string("a"), tw.render(0));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(1));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(2));
    CPPUNIT_ASSERT_EQUAL(std::string("abc"), tw.render(3));
    CPPUNIT_ASSERT_EQUAL(std::string("a"), tw.render(4));

    tw.setRawString("a,b,,c,<<de");
    CPPUNIT_ASSERT_EQUAL(true, tw.parse());
    CPPUNIT_ASSERT_EQUAL(std::string("a"), tw.render(0));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(1));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(2));
    CPPUNIT_ASSERT_EQUAL(std::string("abc"), tw.render(3));
    CPPUNIT_ASSERT_EQUAL(std::string("ade"), tw.render(4));
}

void BasicCase_tests::TestFrameSkip()
{
	TypeWriter tw;
    tw.setRawString("a,b,[4]c,<<d");
    CPPUNIT_ASSERT_EQUAL(true, tw.parse());
    CPPUNIT_ASSERT_EQUAL(std::string("a"), tw.render(0));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(1));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(2));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(3));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(4));
    CPPUNIT_ASSERT_EQUAL(std::string("abc"), tw.render(5));
    CPPUNIT_ASSERT_EQUAL(std::string("ad"), tw.render(6));

    tw.setRawString("e,f,[4f]g,<<h");
    CPPUNIT_ASSERT_EQUAL(true, tw.parse());
    CPPUNIT_ASSERT_EQUAL(std::string("e"), tw.render(0));
    CPPUNIT_ASSERT_EQUAL(std::string("ef"), tw.render(1));
    CPPUNIT_ASSERT_EQUAL(std::string("ef"), tw.render(2));
    CPPUNIT_ASSERT_EQUAL(std::string("ef"), tw.render(3));
    CPPUNIT_ASSERT_EQUAL(std::string("ef"), tw.render(4));
    CPPUNIT_ASSERT_EQUAL(std::string("efg"), tw.render(5));
    CPPUNIT_ASSERT_EQUAL(std::string("eh"), tw.render(6));

    tw.setRawString("i,j,[4s]k,<<l");
    CPPUNIT_ASSERT_EQUAL(true, tw.parse());tw.print();
    CPPUNIT_ASSERT_EQUAL(std::string("i"), tw.render(0));
    CPPUNIT_ASSERT_EQUAL(std::string("ij"), tw.render(1));
    CPPUNIT_ASSERT_EQUAL(std::string("ij"), tw.render(1 + 4*tw.getFrameRate()-1));
    CPPUNIT_ASSERT_EQUAL(std::string("ijk"), tw.render(1 + 4*tw.getFrameRate()));
    CPPUNIT_ASSERT_EQUAL(std::string("il"), tw.render(1 + 4*tw.getFrameRate()+1));

    tw.setRawString("m,n,[4g]o,<<p");
    CPPUNIT_ASSERT_EQUAL(false, tw.parse());
}
