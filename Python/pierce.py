def pierce(a, b):
  print("[a: {}; b: {}]".format(a, b))
  while b > 0:
    b = a % b
    print(b)


i = 10
for j in range(1, i):
  pierce(i, j)

# pierce(35, 22)
