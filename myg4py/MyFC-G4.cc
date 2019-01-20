#include <boost/python.hpp>

char const* greet(unsigned x)
{
   static char const* const msgs[] = { "hello", "Boost.Python", "world!" };

   if (x > 2)
       throw std::range_error("greet: index out of range");

   return msgs[x];
}

using namespace boost::python;
BOOST_PYTHON_MODULE(hello)
{
    def("greet", greet, "return one of 3 parts of a greeting");
}

