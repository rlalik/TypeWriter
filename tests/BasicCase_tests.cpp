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
    tw.setRawString("a>b>>c><");
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
    tw.setRawString("a>b>>c><<");
    CPPUNIT_ASSERT_EQUAL(true, tw.parse());
    CPPUNIT_ASSERT_EQUAL(std::string("a"), tw.render(0));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(1));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(2));
    CPPUNIT_ASSERT_EQUAL(std::string("abc"), tw.render(3));
    CPPUNIT_ASSERT_EQUAL(std::string("a"), tw.render(4));

    tw.setRawString("a>b>>c><<de");
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
    tw.setRawString("a>b>{4}c><<d");
    CPPUNIT_ASSERT_EQUAL(true, tw.parse());
    CPPUNIT_ASSERT_EQUAL(std::string("a"), tw.render(0));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(1));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(2));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(3));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(4));
    CPPUNIT_ASSERT_EQUAL(std::string("abc"), tw.render(5));
    CPPUNIT_ASSERT_EQUAL(std::string("ad"), tw.render(6));

    tw.setRawString("a>b>{4f}c><<d");
    CPPUNIT_ASSERT_EQUAL(true, tw.parse());
    CPPUNIT_ASSERT_EQUAL(std::string("a"), tw.render(0));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(1));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(2));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(3));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(4));
    CPPUNIT_ASSERT_EQUAL(std::string("abc"), tw.render(5));
    CPPUNIT_ASSERT_EQUAL(std::string("ad"), tw.render(6));

    tw.setRawString("a>b>{4s}c><<d");
    CPPUNIT_ASSERT_EQUAL(true, tw.parse());
    CPPUNIT_ASSERT_EQUAL(std::string("a"), tw.render(0));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(1));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(1 + 4*tw.getFrameRate()-1));
    CPPUNIT_ASSERT_EQUAL(std::string("abc"), tw.render(1 + 4*tw.getFrameRate()));
    CPPUNIT_ASSERT_EQUAL(std::string("ad"), tw.render(1 + 4*tw.getFrameRate()+1));

    tw.setRawString("a>b>{4g}c><<d");
    CPPUNIT_ASSERT_EQUAL(false, tw.parse());
}
