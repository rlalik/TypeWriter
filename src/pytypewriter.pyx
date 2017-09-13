from libcpp cimport bool
from libcpp.string cimport string

cdef extern from "typewriter.h":
    cdef cppclass TypeWriter:
        TypeWriter() except +

        void setFrameRate(int)
        int getFrameRate()

        void setRawString(string);
        string getRawString()

        bool parse();
        string render(int);

        int count()
        bool isEnd()

        void clear()
        void debug()

cdef class PyTypeWriter:
    cdef TypeWriter c_tw      # hold a C++ instance which we're wrapping
    def __cinit__(self,):
        self.c_tw = TypeWriter()

    def setFrameRate(self, fr):
        self.c_tw.setFrameRate(fr)
    def getFrameRate(self):
        return self.c_tw.getFrameRate()

    def setRawString(self, str):
        self.c_tw.setRawString(str)
    def getRawString(self):
        return self.c_tw.getRawString()

    def parse(self):
        return self.c_tw.parse()
    def render(self, frame):
        return self.c_tw.render(frame)

    def count(self):
        return self.c_tw.count()
    def isEnd(self):
        return self.c_tw.isEnd()

    def clear(self):
        self.c_tw.clear()
    def debug(self):
        self.c_tw.debug()
