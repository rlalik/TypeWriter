#include "typewriter.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

TypeWriter::TypeWriter() :
    frame_rate(25),
    nextkey_char('>'), delkey_char('<'), optbeg_char('{'), optend_char('}')
{
}

TypeWriter::~TypeWriter()
{
    clear();
}

void TypeWriter::clear()
{
    for (uint i = 0; i < strings.size(); ++i)
    {
        Frame * f = strings[i].second;
        while (!f)
        {
            Frame * f2 = f->next;
            delete f;
            f = f2;
        }
    }
    strings.clear();
}

bool TypeWriter::parse()
{
    clear();

    std::stringstream ss(raw_string);
    std::string to;
    std::vector<std::string> lines;

    uint lineno = 0;
    while(std::getline(ss, to))
    {
        lines.push_back(to);

        bool ret = parseLine(lineno, to);
        if (!ret)
            return false;

        ++lineno;
    }

    return true;
}

bool TypeWriter::parseLine(uint lineno, const std::string& line)
{
    StringQueue sq;
    sq.first = 0;

    size_t limit = line.length();

    uint frame = 0;
    std::string frame_text;

    Frame * last_frame = new Frame;
    sq.second = last_frame;
    sq.first = last_frame;

    uint i = 0;
    bool last_action_was_frame_skip = false;
    while (i < limit)
    {
        char c = line[i];
        if (c == nextkey_char)
        {
            ++i;
            ++frame;
            last_action_was_frame_skip = true;
            continue;
        }
        else if (c == optbeg_char)  // open bracket
        {
            if (!last_action_was_frame_skip)
                return false;

            // go to the next char
            ++i;
            if (i == limit) // if end of line reach, parsing error
                return false;

            c = line[i];

            int n = 0;  // stores number of frames to skip
            bool expect_end = false;    // when ending should be expected

            while (c != optend_char)
            {
                if (expect_end)
                    return false;

                // if is digit then add to frames skip number
                if (isdigit(c))
                {
                    int v = c - 48; // quick conv from char to int
                    n = n*10 + v;
                }
                // s if for seconds: mult frames by f. rate
                else if (c == 's')
                {
                    n *= frame_rate;
                    expect_end = true;
                }
                // just frames
                else if (c == 'f')
                {
                    expect_end = true;
                }
                else
                {
                    // unexpected character
                    return false;
                }

                ++i;
                if (i == limit) // if end of line reach, parsing error
                    return false;

                c = line[i];
            }
            ++i;

            frame += n - 1; // add number of frames, -1 to cancel last '>' action
        }
        else
        {
            last_action_was_frame_skip = false;
            // create new or reuse old frame
            if (last_frame->frame != frame)
            {
                Frame * f = new Frame;
                f->frame = frame;
                f->s = last_frame->s;

                // add it to the chain
                f->link(last_frame);

                // move iterator
                last_frame = f;
            }

            // append values
            if (c == delkey_char)
            {
                last_frame->addBypass();
            }
            else
            {
                char buff[2];
                buff[0] = c;
                buff[1] = 0L;
                last_frame->s.append(buff);
            }

            ++i;
        }
    }

    strings.push_back(sq);

    return true;
}

std::string TypeWriter::render(uint frame)
{
    std::stringstream ss;
    for (uint i = 0; i < strings.size(); ++i)
    {
        if (i > 0)
            ss << "\n";

        if (!strings[i].first)
            continue;

        Frame * f = strings[i].second;
        while (true)
        {
            if (!f->next or f->next->frame > frame)
                break;
            else
                f = f->next;
        }
        ss << f->s;
    }

    return ss.str();
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

void tw_init(CTypeWriter * tw)
{
    tw->tw = new TypeWriter;
}

void tw_delete(CTypeWriter * tw)
{
    delete tw->tw;
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

void tw_parse(CTypeWriter * tw)
{
    ((TypeWriter*)tw->tw)->parse();
}

void tw_render(CTypeWriter * tw, unsigned int frame, char * str, int length)
{
    std::strncpy(str, ((TypeWriter*)tw->tw)->render(frame).c_str(), length);
}
