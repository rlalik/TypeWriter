from libcpp cimport bool
from libcpp.string cimport string

cdef extern from "typewriter.h":
    cdef cppclass _TypeWriter "TypeWriter":
        _TypeWriter() except +

        void setFrameRate(int)
        int getFrameRate()

        void setPattern(string)
        string getPattern()

        int parse()
        void printParseResult()
        string render(int)

        int count()
        bool isEnd()

        void clear()
        void debug()

cdef class TypeWriter:
    cdef _TypeWriter c_tw      # hold a C++ instance which we're wrapping
    def __cinit__(self,):
        self.c_tw = _TypeWriter()

    def setFrameRate(self, fr):
        self.c_tw.setFrameRate(fr)
    def getFrameRate(self):
        return self.c_tw.getFrameRate()

    def setPattern(self, str):
        self.c_tw.setPattern(str)
    def getPattern(self):
        return self.c_tw.getPattern()

    def parse(self):
        return self.c_tw.parse()
    def printParseResult(self):
        self.c_tw.printParseResult()

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
