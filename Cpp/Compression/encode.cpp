/*

Name:       Charles Shen
Date:       Wednesday July 13, 2016

*/

#include "encode.h"

#define MAX_BITS_USED   16;

const char            Special_Character   =   3;      // EOT character
const int             Max_BWT_Length      =   2048;
const unsigned short  Max_Dictionary_Size =   65535;

void resetDictionary (map<string, int>& dictionary) {
  dictionary.clear();

  for (unsigned short i = 0; i < 128; ++i) {
    dictionary[string(1, i)] = i;
  }
}

void resetDictionary (map<int, string>& dictionary) {
  dictionary.clear();

  for (unsigned short i = 0; i < 128; ++i) {
    dictionary[i] = string(1, i);
  }
}

string Encode::BWT_Encode (string source) {
  source += Special_Character;
  int srcLength = source.length();
  vector<string> suffixArray = vector<string>();

  for (int i = 0; i < srcLength; ++i) {
    string temp = source.substr(i, srcLength - i);
    temp += source.substr(0, i);
    suffixArray.push_back(temp);
  }

  stable_sort(suffixArray.begin(), suffixArray.end());

  string encoded;
  for (int i = 0; i < srcLength; ++i) {
    #ifdef DEBUG_1
    if (suffixArray[i].at(srcLength - 1) == Special_Character)
      cout << "[$] " << i << endl;
    #endif
    encoded += suffixArray[i].at(srcLength - 1);
  }

  return encoded;
}

string Encode::BWT_Decode (string encoded) {
  #ifdef DEBUG_1
  cout << "Reversing BWT" << endl;
  #endif
  string decoded;

  vector<pair<unsigned char, int> > tuples;
  for (unsigned int i = 0; i < encoded.length(); ++i) {
    tuples.push_back(make_pair(encoded[i], i));
  }

  stable_sort(tuples.begin(), tuples.end());

  vector<int> intArrayN;
  int j;
  for (vector<pair<unsigned char, int> >::const_iterator it = tuples.begin();
       it != tuples.end(); ++it) {
    if (it->first == Special_Character) {
      j = it->second;
      #ifdef DEBUG_1
      cout << "[j] " << j << endl;
      #endif
    }
    intArrayN.push_back(it->second);
  }

  do {
    j = intArrayN[j];
    decoded += encoded[j];
  } while (encoded[j] != Special_Character);

  return decoded.substr(0, decoded.length() - 1);
}

unsigned int Encode::Compress (const string &source, unsigned char *& result) {
  string encoded;
  for (unsigned int i = 0; i < source.length(); i += Max_BWT_Length) {
    encoded += BWT_Encode(source.substr(i, Max_BWT_Length));
  }

  #ifdef DEBUG
  // cout << "[encoded] " << encoded << endl;
  cout << "[encoded length] " << encoded.length() << endl;
  #endif

  vector<unsigned char> resultStr;

  map<string, int> dictionary;
  resetDictionary(dictionary);
  unsigned int dictionarySize = dictionary.size();

  string w;
  bool use2Bytes = false;
  for (string::const_iterator it = encoded.begin(); it != encoded.end(); ++it) {
    char k = *it;
    string wk = w + k;
    if (dictionary.count(wk)) {
      w = wk;
    }
    else {
      int _16bits = dictionary[w];
      if (dictionarySize >= 255) {
        use2Bytes = true;
      }
      // byte 1
      if (use2Bytes){
        resultStr.push_back((_16bits >> 8));
      }
      // byte 0
      resultStr.push_back((_16bits & 0xff));

      #ifdef DEBUG_1
      cout << "(code) " << _16bits << "; (string) |" << w << "|";
      cout << "; (byte 1) " << (_16bits >> 8) << "; (byte 0) " << (_16bits & 0x00ff) << endl;
      #endif

      dictionary[wk] = dictionarySize++;
      w = string(1, k);

      if (dictionarySize >= Max_Dictionary_Size) {
        #ifdef DEBUG
        cout << dictionarySize;
        cout << "; reset in compress" << endl;
        #endif
        resetDictionary(dictionary);
        dictionarySize = dictionary.size();
      }
    }
  }

  if (!w.empty()) {
    int _16bits = dictionary[w];
    // byte 1
    if (use2Bytes){
      resultStr.push_back((_16bits >> 8));
    }
    // byte 0
    resultStr.push_back((_16bits & 0xff));

    #ifdef DEBUG_1
    cout << "(code) " << _16bits << "; (string) |" << w << "|";
    cout << "; (byte 1) " << (_16bits >> 8) << "; (byte 0) " << (_16bits & 0x00ff) << endl;
    #endif
  }

  result = new unsigned char[resultStr.size()];
  copy(resultStr.begin(), resultStr.end(), result);
  return resultStr.size();
}

string Encode::Decompress (unsigned char* codedText, unsigned int length) {
  map<int, string> dictionary;
  resetDictionary(dictionary);
  unsigned int dictionarySize = dictionary.size();

  string w(1, (int) *(codedText));
  string result = w;
  string entry;
  bool _2bytesUsed = false;
  for (unsigned int i = 1; i < length; ++i) {
    unsigned int k = (int) *(codedText + i);
    if (k == 0) {
      _2bytesUsed = true;
    }
    if (_2bytesUsed) {
      k = (((int) *(codedText + i)) << 8) + ((int) *(codedText + i + 1));
      ++i;
    }

    if (k == dictionarySize)
      entry = w + w[0];
    else
      entry = dictionary[k];

    result += entry;
    dictionary[dictionarySize++] = w + entry[0];
    w = entry;

    if (dictionarySize >= Max_Dictionary_Size) {
      #ifdef DEBUG
      cout << dictionarySize;
      cout << "; reset in decompress" << endl;
      #endif
      resetDictionary(dictionary);
      dictionarySize = dictionary.size();
    }
  }

  #ifdef DEBUG
  // cout << "[result] " << result << endl;
  cout << "[result length] " << result.length() << endl;
  #endif

  string decoded;
  for (unsigned int i = 0; i < result.length(); i += Max_BWT_Length + 1)
    decoded += BWT_Decode(result.substr(i, Max_BWT_Length + 1));
  return decoded;
}

#ifdef DEBUG
int main () {
  Encode e;

  string in;
  getline(cin, in);

  // cout << "[source] " << in << endl;
  cout << "[source length] " << in.length() << endl;

  unsigned char* result = NULL;
  int length = e.Compress (in, result);

  // cout << "[compressed] ";
  // for (int i = 0; i < length; ++i) {
  //   cout << *(result + i);
  // }
  // cout << endl;
  cout << "[compressed length] " << length << endl;

  cout << "[ratio] " << (length * 1.0) / (in.length() * 1.0) << endl;

  string decoded = e.Decompress(result, length);
  // cout << "[decompressed] " << decoded << endl;
  cout << "[decompressed length] " << decoded.length() << endl;

  cout << "[equal] " ;
  (decoded == in) ?
    cout << "true" :
    cout << "false";
  cout << endl;

  delete [] result;
}
#endif
