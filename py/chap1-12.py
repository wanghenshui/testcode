#!/usr/bin/python
# -*- coding: utf-8 -*
import re

def test_assert(l):
    assert(l[0])
    print l[1] +'('+ l[2] + ') pass'
    
'''
1.11 匹配邮箱
'''
def mail_check(s):
    matcher='\w+@[\w\.]+.com'
    m=re.match(matcher,s)
    return [m.group()!=None,mail_check.__name__,s]

test_assert(mail_check("a@b.com"))
test_assert(mail_check("a_@b.com"))
test_assert(mail_check("a@_b.com"))
#test_assert(mail_check("a@ b.com"))
#test_assert(mail_check("a @b.com"))
#test_assert(mail_check("_@b.com"))
#test_assert(mail_check(" @b.com"))

'''
1.10 匹配所有复数字符串
1.7-1.9
        匹配所有整数长整数浮点数不过是\d控制字数版本就不做了
        [0-9]{1-9}+
'''
def complex_check(s):
    matcher='\d*(-\d+j)?' #'\d*+(-|+\d*j)'
    m=re.match(matcher,s)
    return [m.group()!=None,complex_check.__name__,s]

test_assert(complex_check("1-5j"))
test_assert(complex_check("1+5j"))
test_assert(complex_check("1 + 5j"))
test_assert(complex_check("1"))
test_assert(complex_check("5j"))
'''
1.6 匹配网址 1.12类似，不过是扩展域名。就不考虑了。

'''
def net_check(s):
    matcher='^w{3}\.\w+\.com$'
    m=re.match(matcher,s)
    return [m.group()!=None,net_check.__name__,s]


test_assert(net_check("www.a.com"))
test_assert(net_check("www._a.com"))
test_assert(net_check("www.a_.com"))
#test_assert(net_check("www. a.com"))
'''
1.5 匹配数字空格英文
'''
def street(s):
    matcher='[0-9]+(\s[a-zA-Z]+)+'
    m=re.match(matcher,s)
    return [m.group()!=None,street.__name__,s]    

test_assert(street("12345 abc"))
test_assert(street('1 a b b c'))
#test_assert(street('a'))
#test_assert(street('1 '))
#test_assert(street('1a'))
    
'''
1.4 标识符？
'''
def name(s):
    matcher='_*|[a-zA-Z]*\w+'
    m=re.match(matcher,s)
    return [m.group()!=None,name.__name__,s]

#test_assert(name('233'))
test_assert(name('w_w'))
test_assert(name('name'))
#test_assert(name(''))
#test_assert(name(' '))
_1 = 2
print _1
test_assert(name('_1'))
test_assert(name('_d'))
test_assert(name('_1_d'))


'''
1.3 match a\s or a\.
'''
def dot(s):
    matcher = '[a-zA-Z]+[\s|\.]'
    m=re.match(matcher,s)
    #print m.group()+'|'
    return [m.group()!=None,dot.__name__,s,]
test_assert(dot('a b'))
#test_assert(dot('1 b'))
test_assert(dot('a '))
#test_assert(dot(''))
#test_assert(dot('.'))
test_assert(dot('a.'))
#test_assert(dot(' aab.'))
#test_assert(dot('.b.'))
#test_assert(dot(' b'))
'''
1.2 match a b
'''
def blank(s):
    matcher = '\w+\s'
    m=re.match(matcher,s)
    return [m.group()!=None,blank.__name__,s,]


test_assert(blank('a b'))
test_assert(blank('aaaaa b'))
test_assert(blank('a bbbbbbb'))
test_assert(blank('aaaaaa bbbbbbb'))
#test_assert(blank('aaa'))
'''
    1.1 bat bit but hat hit hut

    ([bh][aiu]t)
'''
def aiu(s):
    matcher = '[bh][aiu]t'
    m=re.match(matcher,s)
    return [m.group()!=None,aiu.__name__,s]

test_assert(aiu('bat'))
test_assert(aiu('but'))
test_assert(aiu('bit'))
test_assert(aiu('hat'))
test_assert(aiu('hut'))
test_assert(aiu('hit'))

#test_assert(aiu('abc'))

    
