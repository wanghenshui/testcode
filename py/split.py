source='"aaaaa":"bbbbb","content":"blahblah"'
substring_list=source.split(',')
for substr in substring_list:
    index = substr.find("content")
    if(index is not -1):
        print(substr[index:])
    else:
        print("skip")
    
