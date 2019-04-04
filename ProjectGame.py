import pygame


class Rectangle:
    def getxys(self, x1, y1, size1):
        self.x = x1
        self.y = y1
        self.size = size1

    def draw(self):
        pygame.draw.rect(screen, color, pygame.Rect(self.x, self.y, self.size, self.size))


rectangles = []
for i in range(4):
    for j in range(13):
        rectangles.append(Rectangle)
        rectangles[-1].getxys(i * 31, j * 31, 30)


pygame.init()
screen = pygame.display.set_mode((400, 300))
done = False
is_blue = True
x = 185
y = 250

clock = pygame.time.Clock()

while not done:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True
        if event.type == pygame.KEYDOWN and event.key == pygame.K_SPACE:
            is_blue = not is_blue

    pressed = pygame.key.get_pressed()
    if pressed[pygame.K_LEFT]:
        x -= 5
    if pressed[pygame.K_RIGHT]:
        x += 5

    if x > 340:
        x = 340
    elif x < 0:
        x = 0

    screen.fill((0, 0, 0))
    if is_blue:
        color = (0, 128, 255)
    else:
        color = (255, 100, 0)

    pygame.draw.rect(screen, color, pygame.Rect(x, y, 60, 20))


    pygame.display.flip()
    clock.tick(60)
