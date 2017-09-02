#include "typewriter.h"
#include "unistd.h"

int main(int argc, char ** argv)
{
    TypeWriter tw;
    tw.setFrameRate(2);
    tw.setRawString("T>h>i>s>> is>{2} a>n>> e>x>m>a><<a>m>p>l>e");

    tw.parse();

    uint total_sec = 10;
    uint fr = tw.getFrameRate();
    ulong step = 1000000 / fr;

    std::string last_str;
    for (uint i = 0; i < total_sec * fr; ++i)
    {
        std::string str = tw.render(i);
        if (str != last_str)
        {
//             for (uint j = 0; j < str.length(); ++j)
//                 printf("\b");

            printf("%s\n", str.c_str());
            fflush(stdout);
            last_str = str;
        }
        usleep(step);
    }

    return 0;
}
