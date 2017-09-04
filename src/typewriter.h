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
    int parseString(const std::string & line, int start_frame);

    struct ParseOptions;
    int parseOptions(const std::string& line, uint & i, ParseOptions & po);
    int parseMacro(const std::string& line, uint & i, uint & frame);

    void insertChar(char c, uint frame);
    void insertString(const std::string & str, uint frame);
    void insertBypass(uint frame);

    uint getFrameSkipFromOptions(const ParseOptions & po, bool steps = false);

    Frame * getOrInsertFrame(uint frame);

private:
    size_t frame_rate;

    std::string raw_string;

    StringQueue sq;   // strings
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
