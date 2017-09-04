#ifndef TYPEWRITER_H
#define TYPEWRITER_H

// for C-interface
struct CTypeWriter
{
    void * tw;
};

#ifdef __cplusplus

#include <string>
#include <vector>

using namespace std;

struct Frame
{
    Frame();

    uint frame;
    std::string s;

    void print();
    void link(Frame * p);
    void addBypass();

    Frame * next;
    Frame * prev;
    Frame * bypass;
};

struct StringQueue {
    Frame * first;
    Frame * current;
    Frame * last;
};

class TypeWriter
{
public:
    TypeWriter();
    virtual ~TypeWriter();

    void setFrameRate(uint fr) { frame_rate = fr; }
    uint getFrameRate() const { return frame_rate; }

    void setRawString(const std::string & str) { raw_string = str; }
    std::string getRawString() const { return raw_string; }

    bool parse();
    std::string render(uint frame);

    void clear();

private:
    int parseLine(uint lineno, const std::string & line, int start_frame);

    struct ParseOptions;
    int parseOptions(const std::string& line, uint & i, ParseOptions & po);

private:
    size_t frame_rate;

    const char command_char;
    const char nextframe_char;
    const char nextstep_char;
    const char delkey_char;
    const char optbeg_char;
    const char optend_char;
    const char rangebeg_char;
    const char rangeend_char;
    const char escape_char;

    std::string raw_string;

    std::vector<StringQueue> strings;   // strings
};

#else

typedef
    struct CTypeWriter
        TypeWriter;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#if defined(__STDC__) || defined(__cplusplus)

extern void tw_init(struct CTypeWriter * tw);
extern void tw_delete(struct CTypeWriter * tw);
extern void tw_setFrameRate(struct CTypeWriter * tw, unsigned int fr);
extern unsigned int tw_getFrameRate(struct CTypeWriter * tw);
extern void tw_setRawString(struct CTypeWriter * tw, const char * str);
extern int tw_parse(struct CTypeWriter * tw);
extern void tw_render(struct CTypeWriter * tw, unsigned int frame, char * str, int length);

#endif
#ifdef __cplusplus
}
#endif

#endif /* TYPEWRITER_H */
