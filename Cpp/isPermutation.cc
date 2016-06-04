// Cracking the Coding Interview
// Given two strings, write a method to decide if one is a permutation of the other
// Assuming ASCII

#include <string>

bool isPermutation (const std::string& s, const std::string& t) {
  int sLength = s.length();
  int tLength = t.length();

  if (sLength != tLength())
    return false;

  int letterCount [256] = {};

  for (int i = 0; i < sLength; ++i) {
    ++ letterCount[s[i]];
  }
}
