#ifndef TYPEWRITER_H
#define TYPEWRITER_H

#include <deque>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Frame
{
    Frame();

    uint frame;
    std::string s;

    void print();
//     std::string & str();
    void link(Frame * p);
    void addBypass();

    Frame * next;
    Frame * prev;
    Frame * bypass;
};

class TypeWriter
{
public:
    TypeWriter();
    virtual ~TypeWriter();

    void setFrameRate(size_t fr) { frame_rate = fr; }
    size_t getFrameRate() const { return frame_rate; }

    void setRawString(const std::string & str) { raw_string = str; }
    std::string getRawString() const { return raw_string; }

    bool parse();
    std::string render(uint frame);

    void clear();

private:
    bool parseLine(uint lineno, const std::string & line);

private:
    size_t frame_rate;

    char nextkey_char;
    char delkey_char;
    char optbeg_char;
    char optend_char;

    std::string raw_string;

    typedef std::pair<Frame*, Frame*> StringQueue; // current frame, string queue

    std::vector<StringQueue> strings;   // strings
};

#endif /* TYPEWRITER_H */
