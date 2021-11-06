#/usr/bin/python3
import tkinter
top = tkinter.Tk()
label = tkinter.Label(top,text='hello world')
label.pack()

q = tkinter.Button(top,text='fuck world',command=top.quit,bg='red',fg='white')
q.pack(fill=tkinter.X,expand=1)

tkinter.mainloop()





