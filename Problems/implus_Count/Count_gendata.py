import random
def ran(st, end):
  return random.randint(st, end)

T1 = 100
T2 = 50000000
T3 = 90000000
T4 = 10000000
T5 = 20000000

n = 100
for t in range(0, 100):
  print n
  for i in range(0, n):
    print ran(1, T1), ran(T4, T5)
    print ran(1, T4), ran(T4, T5), ran(1, 2014)

n = 10000
for t in range(0, 4):
  print n
  for i in range(0, n):
    print ran(1, T1), ran(T2, T3)
    print ran(1, T2), ran(T2, T3), ran(1, 2014)


