/// file: py_module.cpp
/// date: 2022-01-19


#include <pybind11/pybind11.h>


PYBIND11_MODULE(pysimhash, m) {
  m.doc() = "python binding for yanyiwu/simhash.";
}
