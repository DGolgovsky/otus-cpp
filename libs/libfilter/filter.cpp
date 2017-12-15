/*
 * Developed by Dmitry Golgovsky <d.westcoast@aol.com>
 *
 * Description of the class
 *
 */

#include "filter.h"

namespace filter {

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

std::string filter()
{
	std::string result = "";
	return result;
}
}
