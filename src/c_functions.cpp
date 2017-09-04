#include "typewriter.h"

#include <cstring>

void tw_init(CTypeWriter * tw)
{
    tw->tw = new TypeWriter;
}

void tw_delete(CTypeWriter * tw)
{
    delete (TypeWriter*)tw->tw;
    tw->tw = 0;
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
