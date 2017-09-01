#ifndef TYPEWRITER_H
#define TYPEWRITER_H

#include <deque>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
    std::string render(int frame);

private:
    size_t frame_rate;

    char nextkey_char;
    char delkey_char;
    char optbeg_char;
    char optend_char;

    std::string raw_string;

    typedef std::pair<uint, std::string> FrameString;        // frame, string
    typedef std::pair<uint, std::deque<FrameString> > StringQueue; // current frame, string queue

    std::vector<StringQueue> strings;   // strings
};

#endif /* TYPEWRITER_H */
