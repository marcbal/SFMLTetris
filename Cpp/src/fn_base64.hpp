
#include <string>


std::string base64_encode(unsigned char const* data, unsigned int len, bool for_url);
std::string base64_decode(std::string s);
