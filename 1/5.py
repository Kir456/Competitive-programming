import sys

def digit_sum(x):
    res = 0
    while x:
        res += x % 10
        x //= 10
    return res

precomputed = {}

for x in range(10):
    for y in range(10):
        seq = [0, x, y]
        pos = {}
        start = None
        cycle_len = None

        for i in range(3, 1000):
            nxt = digit_sum(seq[i-1] + seq[i-2])
            seq.append(nxt)
            pair = (seq[i-1], seq[i])
            if pair in pos:
                start = pos[pair]
                cycle_len = i - start
                break
            else:
                pos[pair] = i

        L = start + cycle_len - 1
        vals = seq[1:L+1]
        pref = [0] * (L + 1)
        for j in range(1, L + 1):
            pref[j] = pref[j-1] + vals[j-1]

        cycle_sum = pref[start + cycle_len - 1] - (pref[start-1] if start > 1 else 0)
        precomputed[(x, y)] = (pref, start, cycle_len, cycle_sum)

data = sys.stdin.buffer.read().split()
if not data:
    sys.exit(0)
    
it = iter(data)
q = int(next(it))
out = []

for _ in range(q):
    x = int(next(it)); y = int(next(it))
    l = int(next(it)); r = int(next(it))

    pref, start, cycle_len, cycle_sum = precomputed[(x, y)]

    def sum_first(n):
        if n <= 0:
            return 0
        if n < len(pref):
            return pref[n]
        sum_pre = pref[start-1] if start > 1 else 0
        rem = n - (start - 1)
        full = rem // cycle_len
        ost = rem % cycle_len
        extra = 0
        if ost:
            extra = pref[start + ost - 1] - (pref[start-1] if start > 1 else 0)
        return sum_pre + full * cycle_sum + extra

    ans = sum_first(r) - sum_first(l - 1)
    out.append(str(ans))

sys.stdout.write("\n".join(out))
