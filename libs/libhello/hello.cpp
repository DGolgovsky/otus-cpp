#include "hello.h"
#include <ostream>
#include <string>
#include <functional>

using namespace std;

namespace hello
{
void PrintHello(std::ostream& stream)
{
	[out = std::ref(stream << "Hello, ")](){ out.get() << "World!\n"; }();
}
}
