from fractions import Fraction
n,m,B=list(map(int,input().split()))
a=list(map(int,input().split()))
la=[x for x in a if x <= B]
ra=[x for x in a if x >  B]
ans=Fraction(0)

ls = len(la)
rs = len(ra)

while rs > 0:
    tot = Fraction(sum(ra))
    prob = Fraction(1, n)
    for i in range(1, min(m,n-ls+1)+1):
        if prob == Fraction(0):
            break
        ans += tot * prob
        prob /= Fraction(n-i)
        prob *= Fraction(n-i-ls)
    break;

while ls > 0:
    tot = Fraction(sum(la))
    prob = Fraction(1, n)
    for i in range(1, min(m,n-ls+2)+1):
        if prob == Fraction(0):
            break
        ans += tot * prob * Fraction(m-i+1)
        prob /= Fraction(n-i)
        prob *= Fraction(n-i-ls+1)
    break

# for i in range(1, n+1):
    # ans /= Fraction(i)

print(ans.numerator)
print(ans.denominator)
