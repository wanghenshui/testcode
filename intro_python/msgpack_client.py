from msgpackrpc import Client, Address
client = Client(Address("localhost",6789))
num = 9
result = client.call('double',num)
print("call double %s : result %s" %  (num, result))
