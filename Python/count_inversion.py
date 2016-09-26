'''
Find the number of "inverted" pairs in an array.
  i.e. pairs (i, j) such that i < j and A[i] > A[j]
'''
def count_inversion(arr):
  result = []
  if len(arr) < 2:
    return(arr, 0)

  mid = int(len(arr)/2)
  left, leftPiwos = count_inversion(arr[:mid])
  right, rightPiwos = count_inversion(arr[mid:])
  i = 0
  j = 0
  numPiwos = 0
  while i < len(left) and j < len(right):
    if left[i] < right[j]:
      result.append(left[i])
      i += 1
    else:
      result.append(right[j])
      j += 1
      numPiwos += len(left) - i

  result += left[i:]
  result += right[j:]
  return(result, numPiwos + leftPiwos + rightPiwos)

perm = [4, 3, 1, 2]
result, piwos = count_inversion(perm)
print(result)
print(piwos)
