t = int(input())
res = []
for g in range(t):
    n = int(input())
    s = str(input())

    ok = 0
    for i in range(1, n-1):
        a = s[:i]
        c = s[i+1:]
        b = s[i]
        if b in (a+c):
            res.append('YES')
            ok = 1
            break
    
    if ok == 0:
        res.append('NO')

for g in range(t):
    print(res[g])