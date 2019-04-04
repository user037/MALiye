from tkinter import *
from tkinter import filedialog as fd
gridlenght = 25
types = [[1, 'blue'], [2, 'red']]
curtype = 0


def draw(n, m):
    global w, grid
    w.destroy()
    root.configure(bg='white')
    root.geometry(str(gridlenght * 2 * m + 100) + 'x' + str(gridlenght * n))  # window geometry
    root.resizable(0, 0)

    w = Canvas(root, height=gridlenght * n, width=gridlenght * 2 * m)  # canvas for drawing and binds for mouse events
    w.bind('<Button-1>', callbackl)
    w.bind("<Button1-Motion>", callbackl)
    w.bind('<Button-3>', callbackr)
    w.bind("<Button3-Motion>", callbackr)
    w.bind('<Button-2>', clear)
    root.bind("<Key-Right>", keycheckr)
    root.bind('<Key-Left>', keycheckl)

    w.place(x=0, y=0)

    for i in range(n):
        for j in range(m):
            print(grid[i][j], end=' ')
            if grid[i][j] != 0:
                color = types[curtype][1]
            else:
                color = 'white'

            w.create_rectangle(j * 2 * gridlenght, i * gridlenght, j * 2 * gridlenght + 2 * gridlenght,
                               i * gridlenght + gridlenght, fill=color)  # grid
        print()


def callbackl(event):
    global grid
    if event.x // (2 * gridlenght) < m * 2 and event.y // gridlenght < n:
        w.create_rectangle((event.x // (gridlenght * 2)) * 2 * gridlenght, (event.y // gridlenght) * gridlenght,
                           (event.x // (gridlenght * 2)) * 2 * gridlenght + 2 * gridlenght,
                           (event.y // gridlenght) * gridlenght + gridlenght, fill=types[curtype][1])
        grid[(event.y // gridlenght)][(event.x // (2 * gridlenght))] = types[curtype][0]

        print('\n'.join(map(str, grid)))
        print("clicked at", event.x, event.y)


def callbackr(event):
    if event.x // (2 * gridlenght) < m * 2 and event.y // gridlenght < n:
        w.create_rectangle((event.x // (gridlenght * 2)) * 2 * gridlenght, (event.y // gridlenght) * gridlenght,
                           (event.x // (gridlenght * 2)) * 2 * gridlenght + 2 * gridlenght,
                           (event.y // gridlenght) * gridlenght + gridlenght, fill='white')
        grid[(event.y // gridlenght)][(event.x // (2 * gridlenght))] = 0

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
    if file_name[len(file_name) - 4:len(file_name)] == '.lvl':
        file_name = file_name[:len(file_name) - 4]

    file_name += '.lvl'

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
    drawcur()

    menubar = Menu(root)  # menu for handling of files
    filemenu = Menu(menubar, tearoff=0)
    filemenu.add_command(label='Open', command=filedialopen)
    filemenu.add_command(label='Save', command=filedialwrite)
    menubar.add_cascade(label='File', menu=filemenu)

    menubar.add_command(label='Help', command=thelp)
    menubar.add_command(label='Quit', command=destroywindow)

    root.config(menu=menubar)


def fileopen():
    new.destroy()
    file.destroy()
    quitbutton.destroy()

    filedialopen()
    window()


def receive1(event):
    receive()


def receive():
    global n, m, grid
    send.destroy()
    label.destroy()
    n, m = map(int, entry.get().split())
    if m > 20:
        m = 20
    elif m <= 0:
        m = 1

    if n > 25:
        n = 25
    elif n <= 0:
        n = 1

    entry.destroy()
    grid = [[0 for i in range(m)] for j in range(n)]
    window()


def newopen():
    new.destroy()
    file.destroy()
    quitbutton.destroy()

    global entry
    entry = Entry()
    entry.pack(pady=10)

    global label
    label = Label(text='n, m через пробел', height=3)
    label.pack()

    entry.bind('<Return>', receive1)
    entry.focus_force()

    global send
    send = Button(text='Send', command=receive)
    send.pack()


def destroywindow():
    root.destroy()
    quit()


def thelp():
    help = Tk()
    help.geometry('500x500')
    label = Label(help, text='Test')
    label.pack()


def clear(event):
    global n, m, grid
    grid = [[0 for i in range(m)] for j in range(n)]
    draw(n, m)


def keycheckr(event):
    global curtype
    if curtype < len(types) - 1:
        curtype += 1
        drawcur()


def keycheckl(event):
    global curtype
    if curtype > 0:
        curtype -= 1
        drawcur()


def drawcur():
    global c
    c.destroy()
    c = Canvas(root, height=50, width=50)
    c.pack(side='right')
    c.create_rectangle(0, 0, 50, 50, fill=types[curtype][1])


if __name__ == '__main__':
    n = 10
    m = 10
    grid = [[0 for i in range(10)] for j in range(10)]  # grid of blocks
    root = Tk()
    root.title(string='Arkanoid 3000 editor')

    new = Button(text='New', command=newopen)
    new.pack()

    file = Button(text='Open', command=fileopen)
    file.pack()

    quitbutton = Button(text='Quit', command=destroywindow)
    quitbutton.pack()

    w = Canvas()
    c = Canvas()

    root.mainloop()
