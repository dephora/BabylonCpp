#ifndef BABYLON_CORE_STRING_H
#define BABYLON_CORE_STRING_H

#include <babylon/babylon_stl.h>
#include <babylon/babylon_stl_util.h>

namespace BABYLON {
namespace String {

/**
 * Variadic template for concatenating a string.
 */
inline void toString(std::ostream& /*o*/)
{
}

template <class T, class... Ts>
inline void toString(std::ostream& o, const T& t0, const Ts&... ts)
{
  o << t0;
  toString(o, ts...);
}

/**
 * @brief Joins two or more values.
 * @param t0, t1, ..., tn Required. The values to be joined.
 * @return A new String, containing the text of the values.
 */
template <class... T>
inline string_t concat(const T&... t0)
{
  std::ostringstream o;
  toString(o, t0...);
  return o.str();
}

/**
 * @brief Checks if a string contains the other substring.
 * @param s. The string to check.
 * @param toCheck. The substring to search for.
 * @return A boolean value, whether or not the string contains the substring.
 */
inline bool contains(const string_t& s, const string_t& toCheck)
{
  return (s.find(toCheck) != string_t::npos);
}

/**
 * @brief Returns the number of occurrences of the string str in the other
 * string s.
 * @param s. The source string.
 * @param str. The string to search for and count.
 * @return A number, representing the number of occurrences of the string str.
 */
inline size_t count(const string_t& s, const string_t& str)
{
  size_t count = 0;
  size_t nPos  = s.find(str, 0); // first occurrence
  while (nPos != string_t::npos) {
    ++count;
    nPos = s.find(str, nPos + 1);
  }
  return count;
}

/**
 * Variadic template for concatenating a string.
 */
inline void charCodeToString(std::ostream& /*o*/)
{
}

template <class T, class... Ts>
inline void charCodeToString(std::ostream& o, const T& t0, const Ts&... ts)
{
  o << static_cast<char>(t0);
  charCodeToString(o, ts...);
}

/**
 * @brief Escapes a character.
 * @param character The character to escape.
 * @return The escaped character.
 */
inline string_t escape(char character)
{
  static const unordered_map_t<char, string_t> escapedSpecialCharacters
    = {{'.', "\\."}, {'|', "\\|"}, {'*', "\\*"}, {'?', "\\?"},  {'+', "\\+"},
       {'(', "\\("}, {')', "\\)"}, {'{', "\\{"}, {'}', "\\}"},  {'[', "\\["},
       {']', "\\]"}, {'^', "\\^"}, {'$', "\\$"}, {'\\', "\\\\"}};

  auto it = escapedSpecialCharacters.find(character);
  if (it == escapedSpecialCharacters.end()) {
    return string_t(1, character);
  }

  return it->second;
}

/**
 * @brief Escapes a string.
 * @param s The string to escape.
 * @return The escaped string.
 */
inline string_t escape(const string_t& s)
{
  std::ostringstream ostream;
  ::std::for_each(s.begin(), s.end(), [&ostream](const char character) {
    ostream << escape(character);
  });
  return ostream.str();
}

/**
 * @brief Escapes a list of string.
 * @param ss The list of string to escape.
 * @return The escaped list of string.
 */
inline vector_t<string_t> escape(const vector_t<string_t>& ss)
{
  return stl_util::map(ss, [](const string_t& s) { return escape(s); });
}

/**
 * @brief Checks if a string starts with the other string.
 * @param s. The string to check.
 * @param prefix. The substring to search for.
 * @return A boolean value, whether or not the string starts with the prefix
 * string.
 */
inline bool startsWith(const string_t& s, const string_t& prefix)
{
  if (prefix.size() > s.size()) {
    return false;
  }
  return ::std::equal(prefix.begin(), prefix.end(), s.begin());
}

/**
 * @brief Checks if a string ends with the other string.
 * @param s. The string to check.
 * @param postfix. The substring to search for.
 * @return A boolean value, whether or not the string ends with the postfix
 * string.
 */
inline bool endsWith(const string_t& s, const string_t& postfix)
{
  if (postfix.size() > s.size()) {
    return false;
  }
  return ::std::equal(postfix.rbegin(), postfix.rend(), s.rbegin());
}

/**
 * @brief Converts Unicode values to characters.
 * @param t0, t1, ..., tn Required. One or more Unicode values to be converted.
 * @return A String, representing the character(s) representing the specified
 * unicode number(s).
 */
template <class... T>
inline string_t fromCharCode(const T&... t0)
{
  std::ostringstream o;
  charCodeToString(o, t0...);
  return o.str();
}

/**
 * @brief Returns the position of the first occurrence of a specified value in a
 * string.
 * @param src The string to search in.
 * @param searchvalue The string to search for.
 * @param start At which position to start the search. Default 0.
 * @return A Number, representing the position where the specified searchvalue
 * occurs for the first time, or -1 if it never occurs.
 */
inline int indexOf(const string_t& src, const string_t& searchvalue,
                   size_t start = 0)
{
  int index               = -1;
  string_t::size_type loc = src.find(searchvalue, start);
  if (loc != string_t::npos) {
    index = static_cast<int>(loc);
  }
  return index;
}

/**
 * @brief Returns whether or not the arhument is a digit.
 * @param x Required. The value to check.
 * @return A boolean value, whether or not the argument is a digit.
 */
template <typename T>
inline bool isDigit(T x)
{
  string_t s;
  ::std::regex e("^-?\\d+", ::std::regex::optimize);
  ::std::stringstream ss;
  ss << x;
  ss >> s;
  if (::std::regex_match(s, e)) {
    return true;
  }
  else {
    return false;
  }
}

/**
 * @brief Joins the list using the delimiter character.
 * @param v Required. The list to join.
 * @param delim Required. The delimiter character.
 * @return A new String, containing the joined list.
 */
template <typename T>
inline string_t join(const T& v, char delim)
{
  std::ostringstream s;
  for (const auto& i : v) {
    if (&i != &v[0]) {
      s << delim;
    }
    s << i;
  }
  return s.str();
}

/**
 * @brief Returns the position of the last occurrence of a specified value in a
 * string.
 * @param src The string to search in.
 * @param searchvalue The string to search for.
 * @param start The position where to start the search (searching backwards). If
 * omitted, the default value is the length of the string.
 * @return A Number, representing the position where the specified searchvalue
 * occurs for the first time, or -1 if it never occurs.
 */
inline int lastIndexOf(const string_t& src, const string_t& searchvalue,
                       size_t start)
{
  int index               = -1;
  string_t::size_type loc = src.rfind(searchvalue, start);
  if (loc != string_t::npos) {
    index = static_cast<int>(loc);
  }
  return index;
}

inline int lastIndexOf(const string_t& src, const string_t& searchvalue)
{
  return lastIndexOf(src, searchvalue, src.size());
}

/**
 * @brief Returns the nth character from a char array.
 */
template <unsigned N>
inline char nthChar(const char (&arr)[N], unsigned i)
{
  if (i >= N) {
    return '\0';
  }

  return arr[i];
}

/**
 * Pads a string with a number of occurrences of some character to a certain
 * width.
 */
template <typename T>
void pad(basic_string_t<T>& s, typename basic_string_t<T>::size_type n, T c)
{
  if (n > s.length()) {
    s.append(n - s.length(), c);
  }
}

/**
 * @brief String formatting like sprintf.
 */
template <typename... Args>
inline string_t printf(const string_t& format, Args... args)
{
  size_t size = snprintf(nullptr, 0, format.c_str(), args...) + 1;
  unique_ptr_t<char[]> buf(new char[size]);
  snprintf(buf.get(), size, format.c_str(), args...);
  return string_t(buf.get(), buf.get() + size - 1);
}

/**
 * @brief Inserts the contents of s2 at offset 0 in s1.
 * @param s1 The string to update.
 * @param s2 The string to prepend.
 */
inline void pushFront(string_t& s1, const string_t& s2)
{
  s1.insert(0, s2);
}

namespace {
const string_t defaultChars
  = "abcdefghijklmnaoqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
}

inline string_t randomString(std::size_t len              = 64,
                             const string_t& allowedChars = defaultChars)
{
  ::std::mt19937_64 gen{
    static_cast<::std::mt19937_64>(::std::random_device()())};
  ::std::uniform_int_distribution<std::size_t> dist{0,
                                                    allowedChars.length() - 1};
  string_t ret;
  ret.reserve(len);
  ::std::generate_n(::std::back_inserter(ret), len,
                    [&] { return allowedChars[dist(gen)]; });
  return ret;
}

/**
 * @brief Removes a substring from a string.
 * @param s. The input string.
 * @param subStr. The substring to remove.
 * @return Reference to the updated string.
 */
inline string_t& removeSubstring(string_t& s, const string_t& subStr)
{
  auto n = subStr.length();
  for (auto i = s.find(subStr); i != string_t::npos; i = s.find(subStr)) {
    s.erase(i, n);
  }
  return s;
}

/**
 * @brief Searches a string for a match against a regular expression, and
 * returns the matches, as a vector object.
 * @param s The source string.
 * @param re The value to search for, as a regular expression.
 * @return List with matches.
 */
template <typename T>
inline vector_t<T> regexMatch(const T& s, const ::std::regex& re)
{
  vector_t<T> result;
  ::std::smatch smatch;
  if (regex_search(s, smatch, re)) {
    ::std::copy(smatch.begin(), smatch.end(), ::std::back_inserter(result));
  }

  return result;
}

template <class BidirIt, class Traits, class CharT, class UnaryFunction>
basic_string_t<CharT> inline regexReplace(
  BidirIt first, BidirIt last, const ::std::basic_regex<CharT, Traits>& re,
  UnaryFunction f)
{
  basic_string_t<CharT> s;

  typename ::std::match_results<BidirIt>::difference_type positionOfLastMatch
    = 0;
  auto endOfLastMatch = first;

  auto callback = [&](const ::std::match_results<BidirIt>& match) {
    auto positionOfThisMatch = match.position(0);
    auto diff                = positionOfThisMatch - positionOfLastMatch;

    auto startOfThisMatch = endOfLastMatch;
    ::std::advance(startOfThisMatch, diff);

    s.append(endOfLastMatch, startOfThisMatch);
    s.append(f(match));

    auto lengthOfMatch = match.length(0);

    positionOfLastMatch = positionOfThisMatch + lengthOfMatch;

    endOfLastMatch = startOfThisMatch;
    ::std::advance(endOfLastMatch, lengthOfMatch);
  };

  ::std::sregex_iterator begin(first, last, re), end;
  ::std::for_each(begin, end, callback);

  s.append(endOfLastMatch, last);

  return s;
}

/**
 * @brief Uses a regular expression to perform substitution on a sequence of
 * characters.
 * @param source The input character sequence.
 * @param reSearch The regular expression string that will be matched against
 * the input sequence.
 * @param replace The regex replacement format string.
 * @return Result of the replacement.
 */
inline string_t regexReplace(const string_t& source, const string_t& reSearch,
                             const string_t& replace)
{
  string_t result;
  ::std::regex regex(reSearch, ::std::regex::optimize);
  ::std::regex_replace(::std::back_inserter(result), source.begin(),
                       source.end(), regex, replace);
  return result;
}

/**
 * @brief Uses a regular expression to perform substitution on a sequence of
 * characters.
 * @param source The input character sequence.
 * @param reSearch The regular expression that will be matched against the input
 * sequence.
 * @param replace The regex replacement format string.
 * @return Result of the replacement.
 */
template <class Traits, class CharT, class UnaryFunction>
inline string_t regexReplace(const string_t& source,
                             const ::std::basic_regex<CharT, Traits>& reSearch,
                             UnaryFunction f)
{
  return regexReplace(source.cbegin(), source.cend(), reSearch, f);
}

/**
 * @brief Returns a new string with a specified number of copies of the string
 * it was called on.
 * @param str The string to repeat.
 * @param count The number of times the original string value should be repeated
 * in the new string.
 * @return A String, a new string containing copies of the original string.
 */
inline string_t repeat(const string_t& str, size_t count)
{
  string_t result;
  result.reserve(count * str.length());
  for (size_t i = 0; i < count; ++i) {
    result += str;
  }
  return result;
}

/**
 * @brief Searches a string for a specified value and replaces the specified
 * values.
 * @param source The source string where the specified value(s) should replaced
 * by the new value.
 * @param search Required. The value that will be replaced by the replace value.
 * @param replace Required. The value to replace the search value with.
 */
inline void replaceInPlace(string_t& source, const string_t& search,
                           const string_t& replace)
{
  size_t pos = 0;
  while ((pos = source.find(search, pos)) != string_t::npos) {
    source.replace(pos, search.length(), replace);
    pos += replace.length();
  }
}

inline string_t slice(const string_t& s, size_t start = 0)
{
  return s.substr(start);
}

/**
 * @brief Splits a string into an array of substrings.
 * @param value Required. The string to split.
 * @param separator Required. Specifies the character to use for splitting the
 * string.
 * @return An Array, containing the splitted values.
 */
inline vector_t<string_t> split(const string_t& value, char separator)
{
  vector_t<string_t> result;
  string_t::size_type p = 0;
  string_t::size_type q;
  while ((q = value.find(separator, p)) != string_t::npos) {
    result.emplace_back(value, p, q - p);
    p = q + 1;
  }
  result.emplace_back(value, p);
  return result;
}

/**
 * @brief Converts a string to lowercase letters.
 * @param source Required. The string to convert.
 * @return A String, representing the value of a string converted to lowercase.
 */
inline string_t toLowerCase(const string_t& source)
{
  string_t lcs = source;
  ::std::transform(lcs.begin(), lcs.end(), lcs.begin(), ::tolower);
  return lcs;
}

/**
 * @brief Converts a string to uppercase letters.
 * @param source Required. The string to convert.
 * @return A String, representing the value of a string converted to uppercase.
 */
inline string_t toUpperCase(const string_t& source)
{
  string_t ucs = source;
  ::std::transform(ucs.begin(), ucs.end(), ucs.begin(), ::toupper);
  return ucs;
}

/**
 * @brief Converts a string to a number.
 * @param str Required. The string to convert.
 * @return A number, representing the numeric value of the string.
 */
template <typename T>
inline T toNumber(const string_t& str)
{
  T value;
  ::std::stringstream ss(str);
  ss >> value;
  return value;
}

/**
 * @brief Converts a number to a string.
 * @param number Required. The number to convert.
 * @return A string, representing the string value of the number.
 */
template <typename T>
inline string_t toString(const T& number)
{
  ::std::stringstream ss;
  ss << number;
  return ss.str();
}

/**
 * @brief Upper-cases the first letter of each word.
 * @param str. The string to titlecase.
 */
inline string_t& toTitleCase(string_t& str)
{
  auto it = str.begin();
  *it     = static_cast<char>(toupper(*it));
  for (; it != str.end() - 1; ++it) {
    if (*it == ' ') {
      *(it + 1) = static_cast<char>(toupper(*(it + 1)));
    }
  }
  return str;
}

/**
 * @brief Strip whitespace from the beginning of a string.
 * @param str The input string.
 * @return Returns a string with whitespace stripped from the beginning of str.
 */
inline string_t& trimLeft(string_t& str)
{
  auto it2 = ::std::find_if(str.begin(), str.end(), [](char ch) {
    return !::std::isspace<char>(ch, ::std::locale::classic());
  });
  str.erase(str.begin(), it2);
  return str;
}

/**
 * @brief Strip whitespace from the end of a string.
 * @param str The input string.
 * @return A string with whitespace stripped from the end of str.
 */
inline string_t& trimRight(string_t& str)
{
  auto it1 = ::std::find_if(str.rbegin(), str.rend(), [](char ch) {
    return !::std::isspace<char>(ch, ::std::locale::classic());
  });
  str.erase(it1.base(), str.end());
  return str;
}

/**
 * @brief Removes leading and trailing whitespace characters from a string.
 * @param str The input string.
 * @return The string with whitespace stripped from the beginning end of str.
 */
inline string_t& trim(string_t& str)
{
  return trimLeft(trimRight(str));
}

/**
 * @brief Removes leading and trailing whitespace characters from a string.
 * @param str The input string.
 * @return A copy of the string with whitespace stripped from the beginning end
 * of str.
 */
inline string_t trimCopy(const string_t& str)
{
  auto s = str;
  return trimLeft(trimRight(s));
}

} // end of namespace String
} // end of namespace BABYLON

#endif // end of BABYLON_CORE_STRING_H
