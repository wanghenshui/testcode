#read and write

from sys import argv
script, filename = argv

print "we're going to erase %r"%filename
print "if you don't want that,hit the computer\njust kiding CTRL-C you knew it "
print "if you do want that ,hit return"

raw_input("???")

print "Opening the file ...."
target = open(filename,'w')

print "truncating the file. GOODBYE BITCH"
target.truncate()

print "now i'm going to ask you for three lines"
print  "i'm going to write these to the file BITCH"

line1 = raw_input("line 1:")
line2 = raw_input("line 2:")
line3 = raw_input("line 3:")

target.write(line1)
target.write("\n")
target.write(line2)
target.write("\n")
target.write(line3)
target.write("\n")

print "and finally ,we close it "
target.close()



