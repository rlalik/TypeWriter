/*
 * Copyright (c) 2017 Rafal Lalik rafallalik@gmail.com
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

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
    Frame(uint frame);

    uint frame;
    std::string s;
    int bypass;

    void print();
};

class TypeWriter
{
public:
    TypeWriter();
    virtual ~TypeWriter();

    void setFrameRate(uint fr) { frame_rate = fr; }
    uint getFrameRate() const { return frame_rate; }

    void setRawString(const std::string & str);
    std::string getRawString() const { return raw_string; }

    bool parse();
    std::string render(uint frame);

    bool isEnd() const { return last_used_idx == (int)frames.size()-1; }

    void clear();
    void print() const { for (Frame f : frames) f.print(); }

private:
    int parseString(const std::string & line, int start_frame);

    struct ParseOptions;
    int parseOptions(const std::string& line, uint & i, ParseOptions & po);
    int parseMacro(const std::string& line, uint & i, uint & frame);

    void insertChar(char c, uint frame);
    void insertString(const std::string & str, uint frame);
    void insertBypass(uint frame);

    uint getFrameSkipFromOptions(const ParseOptions & po, bool steps = false);

    uint getOrInsertFrame(uint frame);
    void addBypass(uint idx);

private:
    size_t frame_rate;

    std::string raw_string;

    std::vector<Frame> frames;
    int last_used_idx;
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

extern struct CTypeWriter * tw_init();
extern void tw_delete(struct CTypeWriter * tw);
extern void tw_setFrameRate(struct CTypeWriter * tw, unsigned int fr);
extern unsigned int tw_getFrameRate(struct CTypeWriter * tw);
extern void tw_setRawString(struct CTypeWriter * tw, const char * str);
extern int tw_parse(struct CTypeWriter * tw);
extern void tw_render(struct CTypeWriter * tw, unsigned int frame, char * str, int length);
extern void tw_print(struct CTypeWriter * tw);
extern int tw_isEnd(struct CTypeWriter * tw);
#endif
#ifdef __cplusplus
}
#endif

#endif /* TYPEWRITER_H */
