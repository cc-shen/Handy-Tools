#include <iostream>
#include <climits>
#include <cstring>

void countSort(int* intArr, const int& size, const int& min, const int& range){
  int* sorted = new int [size];
  int* count = new int [range + 1];
  memset(count, 0, sizeof(int[range+1]));  // Initialize all values to 0

  // Count how many of each kind there are (offset by the min)
  for(int i = 0; i < size; ++i){
    ++count[intArr[i] - min];
  }

  // Each element to store the sum of the previous element. This way each
  //    element represents the position of each number in the sorted array
  for(int i = 1; i <= range; ++i){
    count[i] += count[i-1];
  }

  // Construct the sorted array
  for(int i = 0; i < size; ++i){
    sorted[count[intArr[i] - min]-1] = intArr[i];
    --count[intArr[i] - min];
  }

  // Copy the sorted array to original array
  for(int i = 0; i < size; ++i){
    intArr[i] = sorted[i];
  }

  delete [] sorted;
  delete [] count;
}

int main(){
  int num;

  int size;
  std::cin >> size;

  int* intArray = new int [size];
  int min = INT_MAX;
  int max = INT_MIN;

  for (int i = 0; i < size; ++i) {
    std::cin >> num;
    intArray[i] = num;
    if (num > max)
      max = num;
    if (num < min)
      min = num;
  }

  countSort(intArray, size, min, max - min);

  #ifdef DEBUG
  std::cout << "Max is " << max << std::endl;
  std::cout << "Min is " << min << std::endl;
  std::cout << "Range is " << max - min << std::endl;
  #endif

  for (int i = 0; i < size; ++i) {

    #ifdef DEBUG
    std::cout << "intArray[" << i << "] is ";
    #endif

    std::cout << intArray[i] << std::endl;
  }

  delete [] intArray;
}
