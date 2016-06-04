// Cracking the Coding Interview
// Implement a function void reverse(char* str) in C or C++
// which reverses a null- terminated string.

#include <string>

void reverse (char* str) {
  char *end = str;
  char temp;
  if (str) {
    while (*end) {
      end ++;
    }
    -- end;

    while (str < end) {
      temp = *str;
      *str = *end;
      *end = temp;
      str ++;
      end --;
    }
  }
}

void reverse (std::string& str) {
  int strLength = str.length();
  int midIndex = strLength / 2;
  for (int i = ; i <= midIndex; ++i) {
    char temp = str[i];
    str[i] = str[strLength - i];
    str[strLength - i] = temp;
  }
}

std::string reverse_const (const std::string& str) {
  std::string newStr = str;
  return reverse(newStr);
}
