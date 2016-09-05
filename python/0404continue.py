while 1:
    s = raw_input('enter something cowboy')
    if s=='quit':
        break
    if len(s)<3:
        continue
    #ignore the string lens less than 3
    print 'input is of sufficient length'
    
