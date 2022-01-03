PYTHON_CONFIG=/usr/local/bin/python3.11d-config
PYTHON_INCLUDES=$(shell $(PYTHON_CONFIG) --includes)

GCCPLUGINS_DIR:= $(shell $(CC) --print-file-name=plugin)
CPPFLAGS+= -I$(GCCPLUGINS_DIR)/include -I$(GCCPLUGINS_DIR)/include/c-family -I. $(PYTHON_INCLUDES) -I /testing/pybind11/include/

all : pip


clean :
	rm -rf build python_example.egg-info python_example.cpython-311d-x86_64-linux-gnu.so || echo skip
	pip3 uninstall -y python-gcc-bind

pip: clean
	#pip3 uninstall -y python-example
	CFLAGS="-fno-rtti" python3 ./setup.py build
	CFLAGS="-fno-rtti" python3 ./setup.py install

test:
	c++  --save-temps $(CPPFLAGS) -fPIC -fno-rtti -Wall -shared -std=c++11  $(python3 -m pybind11 --includes) example.cpp -o example$(python3-config --extension-suffix)

