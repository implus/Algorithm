keys = """6 2
2 3 6 5 4 10
11 2
2 2 2 4 8 8 8 16 16 16 16
2 2 
2 2
2 1
2 2"""
import random
def ran(st, en):
  return random.randint(st, en);

print keys

maxk = 500000000
maxn = 100000
n = maxn
for t in range(0, 10):
  print n, ran(1, 5)
  for i in range(0, n):
    print ran(1, maxn),
  print ""

n = 1000
for t in range(0, 100):
  print n, ran(1, 5)
  for i in range(0, n):
    print ran(1, 260),
  print ""


n = 1000
for t in range(0, 100):
  print n, ran(1, 5)
  for i in range(0, n):
    print ran(1, 1000),
  print ""








