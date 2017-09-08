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
#include "unistd.h"
#include "string.h"
#include "stdio.h"

int main(int argc, char ** argv)
{
    TypeWriter * tw = tw_init();

    tw_setFrameRate(tw, 2);
    if (argc > 1)
        tw_setRawString(tw, argv[1]);
    else
        tw_setRawString(tw, "T,h,i,s,, is,[2] a,n,, e,x,m,a,<<a,m,p,l,e");

    if (!tw_parse(tw))
        return 1;

    unsigned int total_sec = 10;
    unsigned int fr = tw_getFrameRate(tw);
    unsigned long step = 1000000 / fr;

    char last_str[200] = "";
    char str[200];

    unsigned int i = 0;
    while (!tw_isEnd(tw))
    {
        tw_render(tw, i, str, 200);
        if (strcmp(str, last_str) != 0)
        {
            printf("[%3d] %s\n", i, str);
            strcpy(last_str, str);
        }
        usleep(step);
        ++i;
    }

    tw_delete(tw);

    return 0;
}
