import pygame
from tkinter import *
from tkinter import filedialog as fd
import Project
rectangles = []


def main():
    root.destroy()
    x1 = 400
    y1 = 300
    if rectangles:
        x1 = (m + 2) * 31
        y1 = (n + 2) * 16 + 200
    else:
        for i in range(1, 4):
            for j in range(1, 12):
                c = pygame.Rect(j * 31, i * 16, 30, 15)
                rectangles.append(c)

    ccolor = (0, 128, 255)

    ball = pygame.Rect(200, y1 - 120, 30, 30)
    ballvelx = -3
    ballvely = -3
    ballcolor = (255, 100, 0)

    pygame.init()
    screen = pygame.display.set_mode((x1, y1))
    done = False

    platform = pygame.Rect(175, y1 - 30, 50, 10)
    platformcolor = (150, 90, 140)

    clock = pygame.time.Clock()

    while not done:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                done = True

        screen.fill((0, 0, 0))
        pressed = pygame.key.get_pressed()
        if pressed[pygame.K_LEFT]:
            platform.x -= 5
        elif pressed[pygame.K_RIGHT]:
            platform.x += 5

        if platform.x > x1 - platform.width:
            platform.x = x1 - platform.width
        elif platform.x < 0:
            platform.x = 0
        pygame.draw.rect(screen, platformcolor,  platform)

        for i in range(len(rectangles)):
            if rectangles[i] != 0:
                coll = False
                c = ball.move(ballvelx, 0)
                if c.colliderect(rectangles[i]):
                    ballvelx = -ballvelx
                    coll = True

                c = ball.move(0, ballvely)
                if c.colliderect(rectangles[i]):
                    ballvely = -ballvely
                    coll = True

                if coll:
                    rectangles[i] = 0
                    if rectangles == [0] * len(rectangles):
                        quit()
                    ball.x += ballvelx
                    ball.y += ballvely
                else:
                    pygame.draw.rect(screen, ccolor, rectangles[i])

        if ball.move(ballvelx, ballvely).colliderect(platform):
            ballvely = -ballvely

        ball.x += ballvelx
        ball.y += ballvely

        if ball.x > x1 - ball.width:
            ball.x = x1 - ball.width
            ballvelx = -ballvelx
        elif ball.x < 0:
            ball.x = 0
            ballvelx = -ballvelx

        if ball.y < 0:
            ball.y = 0
            ballvely = -ballvely
        elif ball.y > y1 - ball.width:
            quit()

        pygame.draw.rect(screen, ballcolor, ball)

        pygame.display.flip()
        clock.tick(60)


def openfile():
    global n, m
    file_name = fd.askopenfilename(filetypes=(("Level files", "*.lvl"), ("All files", "*.*")))
    inp = open(file_name)
    n, m = map(int, inp.readline().rstrip().split())
    s = inp.readline().rstrip().split()

    for i in range(n):
        for j in range(m):
            if s[j] == '0':
                rectangles.append(0)
            else:
                rectangles.append(pygame.Rect(j * 31, i * 16, 30, 15))
        s = inp.readline().rstrip().split()

    inp.close()
    main()


def edit():
    root.destroy()
    Project.main()


root = Tk()
root.resizable(0, 0)
Button(text='Play', command=main).pack()
Button(text='Open', command=openfile).pack()
Button(text='Editor', command=edit).pack()
Button(text='Quit', command=quit).pack()
root.mainloop()
