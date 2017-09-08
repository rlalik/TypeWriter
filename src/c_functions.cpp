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

#include "typewriter.h"

#include <cstring>

CTypeWriter * tw_init()
{
    CTypeWriter *ctw = new CTypeWriter;
    ctw->tw = new TypeWriter;
    return ctw;
}

void tw_delete(CTypeWriter * tw)
{
    delete (TypeWriter*)tw->tw;
    delete tw;
    tw = 0;
}

void tw_setFrameRate(CTypeWriter * tw, unsigned int fr)
{
    ((TypeWriter*)tw->tw)->setFrameRate(fr);
}

unsigned int tw_getFrameRate(CTypeWriter * tw)
{
    return ((TypeWriter*)tw->tw)->getFrameRate();
}

void tw_setRawString(CTypeWriter * tw, const char * str)
{
    ((TypeWriter*)tw->tw)->setRawString(str);
}

int tw_parse(CTypeWriter * tw)
{
    return ((TypeWriter*)tw->tw)->parse();
}

void tw_render(CTypeWriter * tw, unsigned int frame, char * str, int length)
{
    std::strncpy(str, ((TypeWriter*)tw->tw)->render(frame).c_str(), length);
}

void tw_print(CTypeWriter * tw)
{
    ((TypeWriter*)tw->tw)->print();
}

int tw_isEnd(CTypeWriter * tw)
{
    return ((TypeWriter*)tw->tw)->isEnd();
}
