from tkinter import *
from tkinter import filedialog as fd
gridlenght = 25


def draw(n, m):
    root.geometry(str(gridlenght * m + 100) + 'x' + str(gridlenght * n + 200))  # window geometry
    root.resizable(0, 0)

    global w, grid
    w = Canvas(root, height=gridlenght * n, width=gridlenght * m)  # canvas for drawing and binds for mouse events
    w.bind("<Button-1>", callbackl)
    w.bind('<Button-3>', callbackr)
    w.place(x=0, y=0)

    for i in range(n):
        for j in range(m):
            print(grid[i][j], end=' ')
            if grid[i][j] == 1:
                color = 'blue'
            else:
                color = 'white'

            w.create_rectangle(j * gridlenght, i * gridlenght, j * gridlenght + gridlenght, i * gridlenght + gridlenght,
                               fill=color)  # grid
        print()

def callbackl(event):
    global grid
    w.create_rectangle((event.x // gridlenght) * gridlenght, (event.y // gridlenght) * gridlenght,
                       (event.x // gridlenght) * gridlenght + gridlenght,
                       (event.y // gridlenght) * gridlenght + gridlenght, fill='blue')
    grid[(event.y // gridlenght)][(event.x // gridlenght)] = 1
    print('\n'.join(map(str, grid)))
    print("clicked at", event.x, event.y)


def callbackr(event):
    w.create_rectangle((event.x // gridlenght) * gridlenght, (event.y // gridlenght) * gridlenght,
                       (event.x // gridlenght) * gridlenght + gridlenght,
                       (event.y // gridlenght) * gridlenght + gridlenght, fill='white')
    grid[(event.y // gridlenght)][(event.x // gridlenght)] = 0
    print('\n'.join(map(str, grid)))
    print("clicked at", event.x, event.y)


def filedialopen():
    global grid, n, m
    file_name = fd.askopenfilename(filetypes=(("Level files", "*.lvl"), ("All files", "*.*")))
    inp = open(file_name)
    n, m = map(int, inp.readline().rstrip().split())

    s = inp.readline().rstrip()
    grid = []
    while s:
        grid.append(list(map(int, s.split())))
        s = inp.readline().rstrip()

    inp.close()
    draw(n, m)


def filedialwrite():
    global grid, n, m
    file_name = fd.asksaveasfilename(filetypes=(("Level files", "*.lvl"), ("All files", "*.*")))
    out = open(file_name, 'w')
    print(n, m, file=out)
    for i in range(n):
        for j in range(m):
            print(grid[i][j], file=out, end=' ')
        print(file=out)
    out.close()


def window():
    global n, m
    new.destroy()
    file.destroy()

    draw(n, m)

    menubar = Menu(root)  # menu for handling of files
    filemenu = Menu(menubar, tearoff=0)
    filemenu.add_command(label='Open', command=filedialopen)
    filemenu.add_command(label='Save', command=filedialwrite)
    menubar.add_cascade(label='File', menu=filemenu)

    root.config(menu=menubar)


def fileopen():
    new.destroy()
    file.destroy()

    filedialopen()
    window()


def receive():
    global n, m, grid
    send.destroy()
    label.destroy()
    n, m = map(int, entry.get().split())
    entry.destroy()
    grid = [[0 for i in range(m)] for j in range(n)]
    window()


def newopen():
    new.destroy()
    file.destroy()

    global entry
    entry = Entry()
    entry.pack(pady=10)

    global label
    label = Label(text='n, m через пробел', height=3)
    label.pack()

    global send
    send = Button(text='Send', command=receive)
    send.pack()


if __name__ == '__main__':
    n = 10
    m = 10
    grid = [[0 for i in range(10)] for j in range(10)]  # grid of blocks
    root = Tk()

    new = Button(text='New', command=newopen)
    new.pack()

    file = Button(text='Open', command=fileopen)
    file.pack()

    mainloop()
