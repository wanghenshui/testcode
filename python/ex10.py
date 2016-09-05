tabby_cat = "\t i'm tabbed in"
persian_can = "i'm split\n on a line"
backslash_cat = "i'm\\ a \\ cat"

fat_cat = """
i'll do a list
\t* Cat food
\t* Fishies
\t* Catnip\n\t* Grass
"""

print tabby_cat
print persian_can
print backslash_cat
print fat_cat
j = 5
while j > 0:
	for i in ["/","-","|","\\","|"]:
		print "%s\r" %i 
		j=j-1