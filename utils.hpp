#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#include <string>

// string-related
bool IsWhitespace(char what);
std::string TrimLeft(const std::string& what, bool (callback)(char) = IsWhitespace);
std::string TrimRight(const std::string& what, bool (callback)(char) = IsWhitespace);
std::string Trim(const std::string& what, bool (callback)(char) = IsWhitespace);
std::string ToLower(const std::string& what);
unsigned long StrToInt(const std::string& what);
unsigned long HexToInt(const std::string& what);
bool CheckInt(const std::string& what);

// file related
std::string Basename(const std::string& file);
std::string FixSlashes(const std::string& filename);
std::string TruncateSlashes(const std::string& filename);

#endif // UTILS_HPP_INCLUDED
