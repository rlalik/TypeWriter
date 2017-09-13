from distutils.core import setup, Extension
from Cython.Build import cythonize

module = Extension(
    "pytypewriter",
    sources=[
        "src/pytypewriter.pyx",
        "src/typewriter.cpp",
        "src/c_functions.cpp",
        "src/parsing_functions.cpp"
    ],
    language="c++",              # generate C++ code
    extra_compile_args=["-std=c++11"]
)

setup(
    name='pyTypeWriter',
    ext_modules=cythonize(module, build_dir="build")
)
