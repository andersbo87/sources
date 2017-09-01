#coding=UTF-8
import pygame
import sys

pygame.init()
factor=28.4
background_color=(255,255,255) 
screen = pygame.display.set_mode((500,400))
screen.fill(background_color)
pygame.draw.rect(screen, (211,211,211),(1*factor,1*factor,5*factor,4*factor),0)
pygame.draw.rect(screen, (211,211,211), (1*factor, 6*factor, 6.5*factor, 8*factor),0)
tittel="Løsning av oppg2 (alt. sett) i Python 2"
pygame.display.set_caption(tittel)
pygame.display.update()
kjorer = True
while kjorer:
    for hendelse in pygame.event.get():
        if hendelse.type == pygame.QUIT:
            kjorer = False
