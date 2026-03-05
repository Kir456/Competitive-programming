import itertools

MOD = 998244353

def prod_digits(x):
    if x == 0:
        return 0
    res = 1
    while x:
        res *= x % 10
        x //= 10
    return res

n = int(input())
a = list(map(int, input().split()))

ans = 1
found_zero = False

for r in range(1, n + 1):
    for comb in itertools.combinations(a, r):
        s = sum(comb)
        p = prod_digits(s)
        
        if p == 0:
            print(0)
            exit()
        
        ans = (ans * p) % MOD

print(ans)
