import math

result = [1, 1]

def T(n):
  temp = int(math.floor(math.sqrt(n)))
  if len(result) <= n:
    result.append(2 * result[temp])
  print("n: {}; {}".format(n, result[n]))

for i in range (1, 2147483647):
  T(i)
