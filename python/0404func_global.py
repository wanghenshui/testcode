def func():
      global x
      print 'x is ',x
      x = 2
      print'changed local x to',x

x = 50
func()
print 'value of x is',x
