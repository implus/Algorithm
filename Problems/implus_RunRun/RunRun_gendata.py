import random
def ran(st, end):
  return random.randint(st, end)

M = 100000
n = 100000
m = 100000
for t in range(0, 10):
  print ran(1, M), ran(-M, M)
  print n
  for i in range(0, n):
    print ran(-M, M), ran(-M, M)
  print m
  for i in range(0, m):
    print ran(-M, M), ran(-M, M)

n = 1000
m = 1000
for t in range(0, 100):
  print ran(1, M), ran(-M, M)
  print n
  for i in range(0, n):
    print ran(-M, M), ran(-M, M)
  print m
  for i in range(0, m):
    print ran(-M, M), ran(-M, M)


