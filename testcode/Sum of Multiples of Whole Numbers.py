a=[]
b=[]
def multiples_of_3(n):
     i=1
     for i in range(n):   # stops at 1 less than the value passed to `range`
        m=i*3
        if(m<n):
            a.append(m)

def multiples_of_5(n):
     j=1
     for j in range(n):   # could change to 201 and still work
        k=j*5
        if(k<n):
            b.append(k)

if __name__ == "__main__":
    n=input()
    multiples_of_3(n)
    multiples_of_5(n)

    print sum(set(a+b))