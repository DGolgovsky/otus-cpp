#ifndef _FILTER_H_
#define _FILTER_H_

#include <string>
#include <sstream>
#include <vector>

namespace filter {

std::vector<std::string> split(const std::string &, char);

std::string filter();
}

#endif
