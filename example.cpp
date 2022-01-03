#include <pybind11/pybind11.h>
#include <pybind11/detail/type_caster_base.h>
#include "gcc-c-api/gcc-function.h"
#include "gcc-c-api/gcc-location.h"
#if (GCC_VERSION >= 4009)
#include "context.h"
#include "pass_manager.h"
#include "tree-pass.h"
#endif

class PyGccRtlPass : public rtl_opt_pass
{
public:

};

class Mopt_pass2
{
public:
  Mopt_pass2(){
  }
};


class Mopt_pass  {
public:
  opt_pass * _pass;
  
  Mopt_pass(): _pass(0) {}
  Mopt_pass(opt_pass * v):_pass(v) {}
  
};

class MContext  {
public:

  static long int get() {
    return(long int) g;
  }
  static Mopt_pass * get_all_passes() {
    return (Mopt_pass*) g->get_passes()->all_passes;
  }
};

namespace py = pybind11;

// class GCCWrapper {
// public :
//   static MContext * get () {
//     return (MContext*)g;
//   }
// };

//autotype(opt_pass, opt_pass_info)
//autotype2(opt_pass, opt_pass_info)
autotype(Mopt_pass, mopt_pass_info)
autotype2(Mopt_pass, mopt_pass_info)
autotype(MContext, mcontext_info2)
autotype(Mopt_pass* (*)(), mcontext_info3)
autotype(long int (*)(),long_opt)
///autotype(opt_pass* (*)(Mopt_pass*), optfun)
autotype(PyGccRtlPass, rtloptfun)
//autotype((* src)), opt_src)


PYBIND11_MODULE(python_gcc_bind, m) {

  //py::class_<GCCWrapper> gcc(m,"GCC");
  //gcc.def(py::init<>());
  //gcc.def("get",&GCCWrapper::get);

  py::class_<MContext> context(m,"Context");
  context.def(py::init<>());
  //context.def("get_passes",&gcc::opt_pass::get_passes);
  context.def("get_all_passes",&MContext::get_all_passes);
  context.def("get_global",&MContext::get);
    
  py::class_<Mopt_pass> pass(m, "Pass");
  pass.def(py::init<>());
  //pass.def("clone",&opt_pass::clone);

  // Method 2: pass parent class_ object:
  py::class_<PyGccRtlPass> rtl_pass(m, "RtlPass");
  
}
