#include "MyDll.h"
#include "MyLib.h"

namespace MyDll {
    std::string getWrappedMessage() {
        return "[MyDll Wrapper] " + MyLib::getMessage();
    }
}
