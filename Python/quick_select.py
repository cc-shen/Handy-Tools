from random import randint

def random_partition(A, left, right):
  pivotIndex = randint(left, right)
  pivotValue = A[pivotIndex]
  A[pivotIndex], A[right] = A[right], A[pivotIndex]  # Move pivot to end
  storeIndex = left
  for i in range(left, right):
    if A[i] < pivotValue:
      A[storeIndex], A[i] = A[i], A[storeIndex]
      storeIndex += 1

  A[right], A[storeIndex] = A[storeIndex], A[right]  # Move pivot to its final place
  return storeIndex

'''
  0-based so p should be at least 0 and r is at most n
'''
def random_select(A, p, r, i):
  assert r > 0
  if p == r - 1:
    return(A[p])

  q = random_partition(A, p, r - 1)
  k = q - p + 1

  if k == i:
    return A[q]
  elif i < k:
    return(random_select(A, p, q - 1, i))
  else:
    return(random_select(A, q + 1, r, i - k))

A = [0, 1, 2, 3, 4]
print(random_select(A, 0, len(A), 1))
