from sys import argv

script,filename = argv

txt = open(filename)

print "ok got file %r:"%filename
print txt.read()

print "type the filename again:"
file_again = raw_input(">>>")

txt_again = open(file_again)

print txt_again.read()