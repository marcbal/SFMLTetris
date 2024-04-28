
#include <string>

/*
 Modifications : adding option for base64url
 using str_replace_car() function in included file to replace characters.
*/
#include "fn_string.hpp"

std::string base64_encode(unsigned char const* , unsigned int len, bool for_url);
std::string base64_decode(std::string/* const&*/ s);
