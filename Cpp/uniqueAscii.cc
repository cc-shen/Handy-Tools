// Cracking the Coding Interview
// 1.1 Implement an algorithm to determine if a string has all unique characters.
// What if you cannot use additional data structures?
// Assume in ASCII, so 256 unique characters

#include <string>

bool UniqueAscii (const std::string& str) {
  int strLength = str.length();

  // Can't be contain unique if length is more than 256
  if (strLength > 256) {
    return false;
  }

  bool uniques [256] = {false};
  int val;
  for (int i = 0; i < strLength; ++i) {
    val = str[i];
    if (uniques[val]) {
      return false;
    }
    uniques[val] = true;
  }
  return true;
}
