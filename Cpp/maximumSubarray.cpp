/*

  Find the subarray such that the sum of its elements are the largest.

*/

struct MaximumSubarray {
  unsigned int left,
  unsigned int right,
  int sum
};

MaximumSubarray findMaximumSubarray(int* A, const unsigned int& low, const unsigned int& high) {
  MaximumSubarray suffixes [high - low];

  suffixes[0] = {low, low + 1, A[low]};

  for (int i = low + 1; i < high; i++) {
    if (suffixes[i - 1].sum < 0) {
      suffixes[i] = {i, i + 1, A[i]};
    } else {
      max_subarray *previous = &suffixes[i - 1];
      suffixes[i] = {previous->left, i + 1, previous->sum + A[i]};
    }
  }

  max_subarray *max = &suffixes[0];

  for (int i = low + 1; i < high; i++) {
    if (max->sum < suffixes[i].sum) {
      max = &suffixes[i];
    }
  }

  return *max;
}
