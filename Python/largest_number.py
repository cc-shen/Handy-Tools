def des_comparer (a, b):
  # Comparing which concatenation order produces a larger number (in string form)
  str_one = a + b
  str_two = b + a
  if (str_one < str_two):
    return 1
  elif str_one == str_two:
    return 0
  else: # str_one > str_two
    return -1

def largest_number (A):
  sorted_A = sorted((str(num) for num in A), cmp=des_comparer)
  result = ""
  for num in sorted_A:
    result += num
  return result

''' Examples '''
print(largest_number([1, 23, 5, 9, 95, 99])) # -> 999955231
print(largest_number([9, 95, 99, 23, 4])) # -> 99995423
