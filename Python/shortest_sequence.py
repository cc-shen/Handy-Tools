def shortest_sequence(n):
  steps_required = 0
  while n > 0:
    steps_required += 1
    if n & 2 == 0:
      n /= 2
    else:
      n -= 1
  return steps_required
