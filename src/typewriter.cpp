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

Frame * TypeWriter::getOrInsertFrame(uint frame)
{
    // create new or reuse old frame
    // by design sq.last->frame cannot be larger than frame
    // take the last frame then FIXME: should we break parser here?

    if (!sq.last)
    {
        Frame * f = new Frame;
        sq.first = f;
        sq.current = f;
        sq.last = f;

        return f;
    }

    if (sq.last->frame > frame)
        return sq.last;

    if (sq.last->frame < frame)
    {
        Frame * f = new Frame;
        f->frame = frame;
        f->s = sq.last->s;

        // add it to the chain
        f->link(sq.last);

        // move iterator
        sq.last = f;
    }

    return sq.last;
}

void TypeWriter::insertChar(char c, uint frame)
{
    char buff[2] = "\0";
    buff[0] = c;
    insertString(buff, frame);
}

void TypeWriter::insertString(const std::string & str, uint frame)
{
    Frame * f = getOrInsertFrame(frame);

    f->s.append(str);
}

void TypeWriter::insertBypass(uint frame)
{
    Frame * f = getOrInsertFrame(frame);

    f->addBypass();
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
