def extgcd(a, b):
  if b==0:
    return 1, 0, a
  else:
    x, y, g = extgcd(b, a%b)
    return y, x-a//b*y, g

def CRT(A, M):
  sa = 0
  sm = 1
  for a, m in zip(A, M):
    x, y, g = extgcd(m, sm)
    assert (a-sa)%g==0
    sa = (sa*x*m+a*y*sm)//g
    sm *= m//g
  return sa%sm, sm

A = [2, 3, 2]
M = [3, 5, 7]
# (23, 105)
print(CRT(A, M))
