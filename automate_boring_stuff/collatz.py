#!/usr/bin/python

def collatz(num):
    if not num % 2 :
        return num//2
    else:
        return num*3+1

if __name__=='__main__':
    number=input(u"number and enter:")
    res=collatz(number)
    while res!=1:
        print res
        res=collatz(res)

    print res

