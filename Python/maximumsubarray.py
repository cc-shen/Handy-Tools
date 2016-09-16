def maxSubrangeSum(x, n):
  maxSoFar = 0
  maxSuffixSum = 0
  maxStartIndex = 0
  startIndex = 0
  maxEndIndex = -1

  for i in range(0, n):
    maxSuffixSum = max(0, maxSuffixSum + x[i])
    if maxSuffixSum == 0:
      startIndex = i + 1
    if maxSuffixSum > maxSoFar:
      maxSoFar = maxSuffixSum
      maxStartIndex = startIndex
      maxEndIndex = i

  return maxSoFar, maxStartIndex, maxEndIndex

# x = [-2, -3, 4, -1, -2, 1, 5, -3]
# x = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
x = [-2, -1, -3, -4, -1, -2, -1, -5, -4]
n = len(x)
maxNum, start, end = maxSubrangeSum(x, n)
print("Maximum is {}".format(maxNum))
print("Start at '{}' and end at '{}'".format(start, end))
print(x[start:end + 1])
