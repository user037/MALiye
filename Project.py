from tkinter import *
from tkinter import filedialog as fd


def callbackl(event):
    global grid
    w.create_rectangle((event.x // 50) * 50, (event.y // 50) * 50, (event.x // 50) * 50 + 50, (event.y // 50) * 50 + 50, fill='blue')
    grid[(event.y // 50)][(event.x // 50)] = 1
    print('\n'.join(map(str, grid)))
    print("clicked at", event.x, event.y)


def callbackr(event):
    w.create_rectangle((event.x // 50) * 50, (event.y // 50) * 50, (event.x // 50) * 50 + 50, (event.y // 50) * 50 + 50, fill='white')
    grid[(event.y // 50)][(event.x // 50)] = 0
    print('\n'.join(map(str, grid)))
    print("clicked at", event.x, event.y)


def filedialopen():
    file_name = fd.askopenfilename(filetypes=(("Level files", "*.lvl"), ("All files", "*.*")))
    inp = open(file_name)
    s = inp.readline()
    while s:
        print(s.rstrip())
        s = inp.readline()

    inp.close()


def filedialwrite():
    global grid
    file_name = fd.asksaveasfilename(filetypes=(("Level files", "*.lvl"), ("All files", "*.*")))
    out = open(file_name, 'w')
    print(10, 10, file=out)
    for i in range(10):
        for j in range(10):
            print(grid[i][j], file=out, end=' ')
        print(file=out)
    out.close()


grid = [[0 for i in range(10)] for j in range(10)]
root = Tk()
root.geometry('700x600')
root.resizable(0, 0)

w = Canvas(root, width=500, height=500)
w.bind("<Button-1>", callbackl)
w.bind('<Button-3>', callbackr)
w.place(x=0, y=0)
w.create_rectangle(2, 2, 400, 400)

for i in range(10):
    for j in range(10):
        w.create_rectangle(i * 50, j * 50, i * 50 + 50, j * 50 + 50, fill='white')

buttonopen = Button(text="Открыть", command=filedialopen)
buttonopen.pack(side='right')

buttonwrite = Button(text='Сохранить', command=filedialwrite)
buttonwrite.pack(side='bottom')

mainloop()

