#include "typewriter.h"
#include <iostream>
#include <string>

using namespace std;

TypeWriter::TypeWriter() :
    nextkey_char('>'), delkey_char('<'), optbeg_char('{'), optend_char('{')
{
}

TypeWriter::~TypeWriter()
{
}

bool TypeWriter::parse()
{
}

std::string TypeWriter::render(int frame)
{
    return "";
}
