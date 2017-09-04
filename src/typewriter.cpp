#include "typewriter.h"
#include <string>
#include <sstream>

using namespace std;

TypeWriter::TypeWriter() : frame_rate(25)
{
    sq.first= nullptr;
    sq.current = nullptr;
    sq.last = nullptr;
}

TypeWriter::~TypeWriter()
{
    clear();
}

void TypeWriter::clear()
{
    Frame * f = sq.first;
    while (f)
    {
        Frame * f2 = f->next;
        delete f;
        f = f2;
    }
}

bool TypeWriter::parse()
{
    clear();

    int start_frame = 0;
    int ret = parseString(raw_string, start_frame);
    if (ret < 0)
    {
        fprintf(stderr, "Parsing error:\n%.*s\n", -ret-1, raw_string.c_str());
        fprintf(stderr, "%*c%c\n", -ret-1, ' ', '^');
        return false;
    }

    return true;
}

std::string TypeWriter::render(uint frame)
{
    if (!sq.first)
        return std::string();

    // start with current frame
    Frame * f = sq.current;

    // but if current is ahead 'frame', start from beginning
    if (f->frame > frame)
        f = sq.first;

    while (true)
    {
        if (!f->next or f->next->frame > frame)
            break;
        else
            f = f->next;
    }

    sq.current = f;
    return f->s;
}

Frame::Frame() : frame(0), next(nullptr), prev(nullptr), bypass(nullptr)
{
}

void Frame::print()
{
    printf("%c [%d] %s %c\n",
           prev ? '-' : '|',
           frame, s.c_str(),
           next ? '-' : '|');
}

void Frame::link(Frame* p)
{
    prev = p;
    p->next = this;
}

void Frame::addBypass()
{
    if (bypass)
        bypass = bypass->prev;
    else if (prev)
        bypass = prev->prev;

    if (bypass)
        s = bypass->s;
}
