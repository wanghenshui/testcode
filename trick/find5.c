//编出一个程序能够找出1～n之间含有5这个数字的数？
f(n){return n%10==5||n&&f(n/10);}