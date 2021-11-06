#!/usr/bin/python
# -*- coding: UTF-8 -*-
from urllib import request
#import requests
#import re
#from bs4 import BeautifulSoup
#from distutils.filelist import findall

proxies = {
        'http': 'http://221.202.248.52:80',
    }
user_agent = 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.104 ' \
                 'Safari/537.36 Core/1.53.4295.400'
headers = {'User-Agent': user_agent}

for i in range(0,2):
    url = 'https://sclub.jd.com/comment/productPageComments.action?callback=fetchJSON_comment98vv62004&productId' \
      '=2357091&score=0&sortType=5&page='+str(i)+'&pageSize=10&isShadowSku=0&fold=1'
    page = request.urlopen(url)
# 获得了整个网页的内容
# .read()输出读取的返回值是bytes类型
    contents = page.read()
# 解决乱码
    contents = contents.decode('GBK')
    contents1 = contents.split(',')
    count = 0
    for contents2 in contents1:
        index = contents2.find("content")
        if(index != -1):
            file = open("comments.txt", 'a+')

            try:
                com = contents2[index+10:-1]
                #print(com)
                file.seek(0)
                com1= file.readlines()
                w=False
                for item in com1:
                    print("com: ",com,"item: ",item)
                    if com in item or item in com:
                        w=False
                        break
                    else:
                        w=True
                        continue

                    if len(com1)<=count:#bug?
                        break
                
                if w:
                    file.writelines(format(com))
                    file.writelines('\n')
                
                if len(com1) == 0:
                        file.writelines(format(com))
                        file.writelines('\n')
                        count = count + 1
            finally:
                file.close()

print(count)
