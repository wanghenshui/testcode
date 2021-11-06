#/usr/bin/python3
import tkinter

def resize(ev=None):
    label.config(font='Helvetica -%d bold' % scale.get())


top = tkinter.Tk()
top.geometry('250x250')

label = tkinter.Label(top,text='hello world',font='Helvetica -12 bold')
label.pack(fill=tkinter.Y,expand=1)

scale = tkinter.Scale(top,from_=10,to=40,orient=tkinter.HORIZONTAL,command=resize)
scale.set(12)
scale.pack(fill=tkinter.X,expand=1)

q = tkinter.Button(top,text='fuck world',command=top.quit,\
                   activeforeground='white',activebackground='red')
q.pack

tkinter.mainloop()





