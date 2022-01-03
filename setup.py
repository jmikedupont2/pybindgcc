import sys

from pybind11 import get_cmake_dir
# Available at setup time due to pyproject.toml
from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup

__version__ = "0.0.1"

# The main interface is through Pybind11Extension.
# * You can add cxx_std=11/14/17, and then build_ext can be removed.
# * You can set include_pybind11=false to add the include directory yourself,
#   say from a submodule.
#
# Note:
#   Sort input source files if you glob sources to ensure bit-for-bit
#   reproducible builds (https://github.com/pybind/python_example/pull/53)

GCCPLUGINS_DIR="/testing/gcc/bin_master/lib/gcc/x86_64-pc-linux-gnu/12.0.0/plugin"
                          
ext_modules = [
        Pybind11Extension("python_gcc_bind",
                                  ["example.cpp"],
                          # Example: passing in the version to the compiled code
                          define_macros = [('VERSION_INFO', __version__)],
                          include_dirs=[
                              GCCPLUGINS_DIR + "/include",
                              GCCPLUGINS_DIR + "/include/c-family",
                          ]


                                  ),
    ]

setup(
        name="python_gcc_bind",
    version=__version__,
        author="James Michael DuPont",
        description="A test project using pybind11",
        long_description="",
        ext_modules=ext_modules,
        extras_require={"test": "pytest"},
        # Currently, build_ext only provides an optional "highest supported C++
        # level" feature, but in the future it may provide more features.
        cmdclass={"build_ext": build_ext},
        zip_safe=False,
        python_requires=">=3.9",
    )
