#/usr/bin/python3

from functools import partial as pto
from tkinter import Tk, Button, X, messagebox
#from messagebox import showinfo,showerror,showwarning
WARN = 'warn'
CRIT = 'crit'
REGU = 'regu'

SIGNS = {
    'do not enter': CRIT,
    'railroad crossing': WARN,
    '55\speed limit': REGU,
    'wrong way': CRIT,
    'merging traffic': WARN,
    'one way': REGU
}

critCB = lambda: messagebox.showerror('Error','Error Button Pressed!')
warnCB = lambda: messagebox.showwarning('Warning','Warning Button Pressed!')
infoCB = lambda: messagebox.showinfo('info', 'Info Button Pressed!')

top = Tk()
top.title("Road Signs")
Button(top,text='QUIT',command=top.quit,bg='red',fg='white').pack()

MyButton = pto(Button,top)
CritButton = pto(MyButton, command=critCB, bg='white',fg='red')
WarnButton = pto(MyButton, command=warnCB, bg='goldenrod1')
ReguButton = pto(MyButton, command=infoCB, bg='white')


for each_sign in SIGNS:
    sign_type = SIGNS[each_sign]
    cmd = '%sButton(text=%r%s).pack(fill=X,expand=True)' %\
          ( sign_type.title(), each_sign,'.upper()' if sign_type == CRIT else '.title()' )
    eval(cmd)

top.mainloop()





