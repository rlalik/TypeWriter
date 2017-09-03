Typewrite is a library to animate behavior of a type writer.

Library parses formatted string and generate chains of string according to the frame. Value of the string can be obtained for any given frame value.

Main feautures
--------------

* uses 'frame' and 'step' units - step should be associated with one second,
* by defualt there is 25 frames per step (second),


String formatting
-----------------
* '>' - next frame
* '>{n}' or '>{nf}' - next n-frames
* '>{ns}' - next n-steps
* '<' - delete string from the last frame (multiple '<' delete more frames)

See also examples/demo.cpp

Minimum example
---------------

```C++
TypeWriter tw;
tw.setFrameRate(2);
tw.setRawString("T>h>i>s>> is>{2} a>n>> e>x>m>a><<a>m>p>l>e");
tw.parse();
for (int i = 0; i < 20; ++i)
    printf("%s\n", tw.render(i).c_str());
```
will produce following chain of strings (numbers in brackets denote frame number):

    [ 0] T
    [ 1] Th
    [ 2] Thi
    [ 3] This
    [ 5] This is
    [ 7] This is a
    [ 8] This is an
    [10] This is an e
    [11] This is an ex
    [12] This is an exm
    [13] This is an exma
    [14] This is an exa
    [15] This is an exam
    [16] This is an examp
    [17] This is an exampl
    [18] This is an example

See also examples/demo.cpp

Installation
------------

```
git clone http://github.com/rlalik/TypeWriter.git
cd TypeWriter
mkdir build
cd build
cmake ..
make
```

C interface
-----------

There are wrapper function allowing to use Library with C code (e.g. MLT), here is set of wrapping function. See examples/demo.c for an example.
```C
typedef struct CTypeWriter TypeWriter;

extern void tw_init(struct CTypeWriter * tw);
extern void tw_finish(struct CTypeWriter * tw);
extern void tw_setFrameRate(struct CTypeWriter * tw, unsigned int fr);
extern unsigned int tw_getFrameRate(struct CTypeWriter * tw);
extern void tw_setRawString(struct CTypeWriter * tw, const char * str);
extern void tw_parse(struct CTypeWriter * tw);
extern void tw_render(struct CTypeWriter * tw, unsigned int frame, char * str, int length);
```