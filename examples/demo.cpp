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
#include <fstream>

int main(int argc, char ** argv)
{
    int index;
    int c;

    int framerate = 25;
    std::string input_file;
    std::string input_string;
    const char * def_str = "T,h,i,s,, is,[2] a,n,, e,x,m,a,<<a,m,p,l,e";

    opterr = 0;

    while ((c = getopt (argc, argv, "f:i:h")) != -1)
    {
        switch (c)
        {
        case 'i':
            input_file = optarg;
            break;
        case 'f':
            framerate = atoi(optarg);
            break;
        case 'h':
        case '?':
            printf("Usage:\n  %s [-f frame_rate] [-i input_file] [string]\n" \
            "    -f  -- frame rate (default=%d)\n" \
            "    -i  -- file to read\n" \
            "    string -- string to use if no file specified (default=\"%s\")\n",
                   argv[0], framerate, def_str);
            return 1;
        default:
            abort ();
        }
    }

    if (input_file.length())
    {
        std::ifstream file(input_file, std::ios::binary | std::ios::ate);
        if (!file.is_open())
            return 1;

        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<char> buffer(size);
        if (file.read(buffer.data(), size))
        {
            input_string = buffer.data();
        }
    }

    if (!input_string.length())
    {
        for (index = optind; index < argc; index++)
        {
            if (index > optind)
                input_string.append(" ");
            input_string.append(argv[index]);
        }
    }

    if (!input_string.length())
        input_string = def_str;

    TypeWriter tw;
    tw.setFrameRate(framerate);
    tw.setRawString(input_string);

    if (!tw.parse())
        return 1;

    uint fr = tw.getFrameRate();
    ulong step = 1000000 / fr;

    uint i = 0;
    std::string last_str;
    while (!tw.isEnd())
    {
        std::string str = tw.render(i);
        if (str != last_str)
        {
            printf("[%3d] %s\n", i, str.c_str());
            last_str = str;
        }
        usleep(step);
        ++i;
    }

    return 0;
}
