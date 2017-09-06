#include "typewriter.h"
#include "unistd.h"
#include "string.h"
#include "stdio.h"

int main(int argc, char ** argv)
{
    TypeWriter tw;
    tw_init(&tw);

    tw_setFrameRate(&tw, 2);
    if (argc > 1)
        tw_setRawString(&tw, argv[1]);
    else
        tw_setRawString(&tw, "T,h,i,s,, is,[2] a,n,, e,x,m,a,<<a,m,p,l,e");

    if (!tw_parse(&tw))
        return 1;

    unsigned int total_sec = 10;
    unsigned int fr = tw_getFrameRate(&tw);
    unsigned long step = 1000000 / fr;

    char last_str[200] = "";
    char str[200];

    unsigned int i = 0;
    while (!tw_isEnd(&tw))
    {
        tw_render(&tw, i, str, 200);
        if (strcmp(str, last_str) != 0)
        {
            printf("[%3d] %s\n", i, str);
            strcpy(last_str, str);
        }
        usleep(step);
        ++i;
    }

    tw_delete(&tw);

    return 0;
}
