#petit programa per convertit un dibuix als codis hex per la ghlcd o com es digui
#si algu mai llegeix aixo el codi es terrorista pero ets lliure de fer-lo servir i distribuir-lo
#pol 

import pygame
from pygame.locals import *
import sys

pygame.init()

grid_size = 20
cols = 15
rows = 8
width = cols * grid_size
height = (rows + 1) * grid_size  
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("de dibuix a hex")

drawing = False
erasing = False
pixels = [[0] * cols for _ in range(rows)]

def draw_grid():
    for x in range(0, width, grid_size):
        pygame.draw.line(screen, pygame.Color('white'), (x, 0), (x, height))
    for y in range(0, height, grid_size):
        pygame.draw.line(screen, pygame.Color('white'), (0, y), (width, y))

def draw_pixels():
    for row in range(rows):
        for col in range(cols):
            if pixels[row][col] == 1:
                pygame.draw.rect(screen, pygame.Color('white'), (col * grid_size, row * grid_size, grid_size, grid_size))

def draw_hex_values():
    font = pygame.font.Font(None, 12)
    for col in range(cols):
        value = 0
        for row in range(rows):
            value |= pixels[row][col] << row
        hex_value = hex(value)[2:].upper()
        text_surface = font.render(hex_value, True, pygame.Color('white'))
        text_rect = text_surface.get_rect(center=(col * grid_size + grid_size // 2, height - grid_size // 2))
        screen.blit(text_surface, text_rect)

def save_to_hex():
    hex_values = []
    for col in range(cols):
        value = 0
        for row in range(rows):
            value |= pixels[row][col] << row
        hex_values.append(hex(value))
    print(", ".join(hex_values))

def start_drawing():
    global drawing, erasing
    drawing = True
    erasing = False

def stop_drawing():
    global drawing, erasing
    drawing = False

def start_erasing():
    global drawing, erasing
    erasing = True
    drawing = False

def handle_mouse_motion(pos):
    x, y = pos
    col = x // grid_size
    row = y // grid_size
    if 0 <= col < cols and 0 <= row < rows:
        if drawing:
            pixels[row][col] = 1
        elif erasing:
            pixels[row][col] = 0

def handle_events():
    global drawing, erasing
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            sys.exit()
        elif event.type == MOUSEBUTTONDOWN:
            if event.button == 1:  
                start_drawing()
            elif event.button == 3: 
                start_erasing()
        elif event.type == MOUSEBUTTONUP:
            stop_drawing()
        elif event.type == MOUSEMOTION:
            if drawing or erasing:
                handle_mouse_motion(event.pos)
        elif event.type == KEYDOWN:
            if event.key == K_RETURN:
                save_to_hex()

# Main loop
while True:
    screen.fill((0, 0, 0))

    draw_grid()
    draw_pixels()
    draw_hex_values()
    handle_events()

    pygame.display.flip()
