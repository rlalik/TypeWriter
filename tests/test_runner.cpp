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

#define CPPUNIT_HAVE_NAMESPACES  1

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TextTestProgressListener.h>

#include <stdexcept>
#include <iostream>

using namespace CppUnit;
using namespace std;

int main (int argc, char* argv[])
{
	std::string testPath = (argc > 1) ? std::string(argv[1]) : "";

	// Create the event manager and test controller
	CppUnit::TestResult controller;

	// Add a listener that colllects test result
	CppUnit::TestResultCollector result;
	controller.addListener( &result );        

	// Add a listener that print dots as test run.
	CppUnit::TextTestProgressListener progress;
	controller.addListener( &progress );      

	TestRunner runner;
	TestFactoryRegistry & registry = TestFactoryRegistry::getRegistry();

	// run all tests if none specified on command line 
	Test * test_to_run = registry.makeTest();
	if (argc > 1)
		test_to_run = test_to_run->findTest(argv[1]);

	runner.addTest( test_to_run );
// 	runner.run(controller);

	try
	{
		std::cout << "Running tests"  /*<<  testPath*/ << endl;;
// 		runner.run( controller, testPath );
		runner.run(controller);

// 		std::cerr << std::endl;

		// Print test in a compiler compatible format.
		CppUnit::CompilerOutputter outputter( &result, std::cerr );
		outputter.write();                      
	}
	catch ( std::invalid_argument &e )  // Test path not resolved
	{
		std::cerr  <<  std::endl  
								<<  "ERROR: "  <<  e.what()
								<< std::endl;
		return 0;
	}

// 	result.runTest();
// 	results.printResults();
// 	runner.prin();

	return result.wasSuccessful() ? 0 : 1;
}
