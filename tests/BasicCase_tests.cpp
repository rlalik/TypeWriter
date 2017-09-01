#include <cppunit/extensions/HelperMacros.h>

#include <typewriter.h>

class BasicCase_tests : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( BasicCase_tests );
	CPPUNIT_TEST( MyTest );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();

protected:
	void MyTest();
};

CPPUNIT_TEST_SUITE_REGISTRATION( BasicCase_tests );

void BasicCase_tests::setUp()
{
}

void BasicCase_tests::MyTest()
{
// 	float fnum = 2.00001f;
// // 	CPPUNIT_FAIL("zxczc");
// 	CPPUNIT_ASSERT_DOUBLES_EQUAL( fnum, 2.0f, 0.0005 );
// 
// 	std::string pattern_string("%%d pattern");
// 	std::string test_string("test pattern");
// 	std::string replace_string("test");
// 
// 	std::string output_string = SmartFactory::placeholder(pattern_string, "%%d", replace_string);
// 	CPPUNIT_ASSERT_EQUAL(output_string, test_string);

	TypeWriter tw;
    tw.setRawString("a>b>>c");

    tw.parse();
    std::cout << tw.render(0) << std::endl;
    std::cout << tw.render(1) << std::endl;
    std::cout << tw.render(2) << std::endl;
    std::cout << tw.render(3) << std::endl;

    CPPUNIT_ASSERT_EQUAL(std::string("a"), tw.render(0));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(1));
    CPPUNIT_ASSERT_EQUAL(std::string("ab"), tw.render(2));
    CPPUNIT_ASSERT_EQUAL(std::string("abc"), tw.render(3));
}
