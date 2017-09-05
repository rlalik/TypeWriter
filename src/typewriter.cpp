#include "typewriter.h"
#include <string>
#include <sstream>

using namespace std;

TypeWriter::TypeWriter() : frame_rate(25), last_used_idx(-1)
{
}

TypeWriter::~TypeWriter()
{
}

void TypeWriter::clear()
{
    frames.clear();
}

void TypeWriter::setRawString(const std::string& str)
{
    raw_string = str;
    frames.reserve(raw_string.length());
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

uint TypeWriter::getOrInsertFrame(uint frame)
{
    // create new or reuse old frame
    // by design last->frame cannot be larger than frame
    // take the last frame then FIXME: should we break parser here?

    uint n = frames.size();
    if (!n)
    {
        frames.push_back(Frame(n, frame));
        last_used_idx = 0;
        return 0;
    }

    if (frames[n-1].frame >= frame)
        return n-1;

    Frame f = Frame(n, frame);
    f.s = frames[n-1].s;
    frames.push_back(f);

    return n;
}

void TypeWriter::insertChar(char c, uint frame)
{
    char buff[2] = "\0";
    buff[0] = c;
    insertString(buff, frame);
}

void TypeWriter::insertString(const std::string & str, uint frame)
{
    uint n = getOrInsertFrame(frame);
    Frame & f = frames[n];

    f.s.append(str);
}

void TypeWriter::insertBypass(uint frame)
{
    uint n = getOrInsertFrame(frame);
    Frame & f = frames[n];

    f.addBypass();
}

std::string TypeWriter::render(uint frame)
{
    uint n = frames.size();
    if (!n)
        return std::string();

    // start with current frame
    Frame f = frames[last_used_idx];

    // but if current is ahead 'frame', start from beginning
    if (f.frame > frame)
        last_used_idx = 0;

    if (frames[last_used_idx].frame > frame)
        return std::string();

    for (; last_used_idx < n-1; ++last_used_idx)
    {
        f = frames[last_used_idx+1];
        if (f.frame > frame)
            return frames[last_used_idx].s;
    }

    return frames[last_used_idx].s;
}

Frame::Frame(uint idx, uint frame) : idx(idx), frame(frame), bypass(-1)
{
}

void Frame::print()
{
    printf("%c [%d at 0x%lx] %s %c\n",
           idx > 0 ? '-' : '|',
           frame, (void*)this, s.c_str(),
           true ? '-' : '|');
}

void Frame::addBypass()
{
    if (bypass == -1)
    {
        if (idx > 0)
            bypass = idx - 1;
    }
    else
    {
        if (bypass > 1)
            --bypass;
    }
}
