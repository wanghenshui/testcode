n = 23
running = True

while 1:#same as ture used to write in embed microcpu
    g = int(raw_input('enter an integer:'))
    if g==n:
        print'congraz you guessed,you won,bitch' #new block starts here
        print"but you dont win any prizes,asshole" #new block ends here
    elif g<n:
        print 'no ,it is a little higher than that'#another block
        #you can do whatever you want in a block
    else :
        print 'no ,it is a little lower than that'
        #you must have guess >number to reach here
else:
    print 'the while loop is over'

print 'done'
