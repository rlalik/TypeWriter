#include "typewriter.h"
#include <string>
#include <sstream>

using namespace std;

TypeWriter::TypeWriter() :
    frame_rate(25),
    command_char(':'), nextframe_char(','), nextstep_char('>'), delkey_char('<'),
    optbeg_char('['), optend_char(']'), rangebeg_char('{'), rangeend_char('}'),
    escape_char('\\')
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
        Frame * f = strings[i].first;
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

    int start_frame = 0;
    uint lineno = 0;
    while(std::getline(ss, to))
    {
        lines.push_back(to);

        int ret = parseLine(lineno, to, start_frame);
        if (ret < 0)
        {
            fprintf(stderr, "Parsing error:\n%s\n", to.c_str());
            fprintf(stderr, "%*c%c\n", -ret-1, ' ', '^');
            return false;
        }

        ++lineno;
    }

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

        // start with current frame
        Frame * f = strings[i].current;

        // but if current is ahead 'frame', start from beginning
        if (f->frame > frame)
            f = strings[i].first;

        while (true)
        {
            if (!f->next or f->next->frame > frame)
                break;
            else
                f = f->next;
        }
        ss << f->s;
        strings[i].current = f;
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
