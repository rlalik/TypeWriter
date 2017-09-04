#include "typewriter.h"

#include <string>

const char command_char = ':';
const char nextframe_char = ',';
const char nextstep_char = '>';
const char delkey_char = '<';
const char optbeg_char = '[';
const char optend_char = ']';
const char rangebeg_char = '{';
const char rangeend_char = '}';
const char escape_char = '\\';

struct TypeWriter::ParseOptions
{
    uint fskip;
    uint sskip;
};

int TypeWriter::parseString(const std::string& line, int start_frame)
{
    size_t limit = line.length();

    uint frame = start_frame;
    std::string frame_text;

    Frame * last_frame = new Frame;
    sq.first = last_frame;
    sq.current = last_frame;

    char check_for_options = 0;
    bool was_escaped = false;
    uint i = 0;
    while (i < limit)
    {
        was_escaped = false;
        check_for_options = 0;

        char c = line[i];
        if (c == escape_char)
        {
            ++i;
            c = line[i];
            was_escaped = true;
        }
        else if (c == nextframe_char)
        {
            // get next char and check whether it is an option
            ++i;
            c = line[i];

            ++frame;    // increase frame number
            check_for_options = nextframe_char;
        }
        else if (c == nextstep_char)
        {
            // get next char and check whether it is an option
            ++i;
            c = line[i];

            frame += frame_rate;
            check_for_options = nextstep_char;
        }
        else if (c == command_char)
        {
            ++i;
            int ret = parseCommand(line, i, frame);
            if (ret < 0)
                return ret;
        }

        if (check_for_options)
        {
            if (c == optbeg_char)
            {
                ParseOptions po = { .fskip = 0, .sskip = 0 };
                int ret = parseOptions(line, i, po);
                if (ret < 0)
                    return ret;

                if (check_for_options == nextframe_char)
                {
                    if (po.fskip > 0)
                    frame += -1 + po.sskip * frame_rate + po.fskip;
                }
                else if (check_for_options == nextstep_char)
                {
                    if (po.sskip > 0)
                        frame += (po.sskip-1) * frame_rate;
                }

                ++i;
                continue;
            }
            continue;
        }

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
        if (!was_escaped and c == delkey_char)
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

    sq.last = last_frame;

    return frame;
}

int TypeWriter::parseOptions(const std::string& line, uint & i, ParseOptions & po)
{
    // go to the next char
    ++i;
    char c = line[i];

    int n = 0;  // stores number of frames to skip

    while (c != optend_char and c)
    {
        // if is digit then add to frames skip number
        if (isdigit(c))
        {
            int v = c - 48; // quick conv from char to int
            n = n*10 + v;
        }
        // s if for seconds: mult frames by f. rate
        else if (c == 's')
        {
            po.sskip = n;
            n = 0;
        }
        // just frames
        else if (c == 'f')
        {
            po.fskip = n;
            n = 0;
        }
        else if (c == ',')
        {
            if (n)
                po.fskip = n;
        }
        else
        {
            // unknown char, return error
            return -i-1;
        }

        ++i;
        c = line[i];
    }

    if (n)
        po.fskip = n;

    ++i;

    return i;
}

int TypeWriter::parseCommand(const std::string& line, uint & i, uint & frame)
{
    char c = line[i];
    if (c == 'c')   // split by characters
    {
        ++i;
        c = line[i];
        if (c != rangebeg_char)
            return -i-1;

        while(c != rangeend_char and c)
        {
        }
    }
    else if (c == 'w')   // split by words
    {
    }
    if (c == 'l')   // split by lines
    {
    }
    else    // error
    {
        return -i-1;
    }
    return i;
}
