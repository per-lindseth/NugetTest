#pragma once
#include <string>

#ifdef MYDLL_EXPORTS
#  define MYDLL_API __declspec(dllexport)
#else
#  define MYDLL_API __declspec(dllimport)
#endif

namespace MyDll {
    MYDLL_API std::string getWrappedMessage();
}
