import xmlrpc.client
proxy = xmlrpc.client.ServerProxy("http://localhost:6789/")
num = 8
result = proxy.double(num)
print ("call double %s : ret is %s" % (num,result))
