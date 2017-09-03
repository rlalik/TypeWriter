#include "typewriter.h"
#include "unistd.h"
#include "string.h"
#include "stdio.h"

int main(int argc, char ** argv)
{
    TypeWriter tw;
    tw_init(&tw);

    tw_setFrameRate(&tw, 2);
    tw_setRawString(&tw, "T>h>i>s>> is>{2} a>n>> e>x>m>a><<a>m>p>l>e");

    tw_parse(&tw);

    unsigned int total_sec = 10;
    unsigned int fr = tw_getFrameRate(&tw);
    unsigned  long step = 1000000 / fr;

    char last_str[200] = "";
    char str[200];
    for (unsigned  int i = 0; i < total_sec * fr; ++i)
    {
        tw_render(&tw, i, str, 200);
        if (strcmp(str, last_str) != 0)
        {
            printf("%s\n", str);
            fflush(stdout);
            strcpy(last_str, str);
        }
        usleep(step);
    }

    return 0;
}
