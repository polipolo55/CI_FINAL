###############################################################################
# Makefile for project 
###############################################################################

## General options
PROJECT = 
MCU = PIC18F45K22
COMPILER = "MPLAB XC8"
TARGET = Release
SHELL = C:\Windows\system32\cmd.exe

## Tools general options
CCFLAGS=--pass1 --errformat="Error at file %%f line %%l column %%c: (%%n) %%s" --warnformat="Warning at file %%f line %%l column %%c: (%%n) %%s" --msgformat="Message at file %%f line %%l column %%c: (%%n) %%s" --chip=18F45K22
LDFLAGS=--output=intel --chip=18F45K22

## Processing Tools
CC=xc8.exe
ASM=xc8.exe
LD=xc8.exe
LIB=xc8.exe
#  C:/Users/Pol/Desktop/uni/CI/CI-FIB-main/Lab/L10/Sobre/PIC18F45K22/Release/Release.hex: TOOL=LD
#  Post: rm startup.as
#  Post: rm Release.as
#     C:/Users/Pol/Desktop/uni/CI/CI-FIB-main/Lab/L10/Sobre/PIC18F45K22/Release/main.p1: TOOL=CC
#        C:/Users/Pol/Desktop/uni/CI/CI-FIB-main/Lab/L10/Sobre/main.c
#     C:/Users/Pol/Desktop/uni/CI/CI-FIB-main/Lab/L10/Sobre/PIC18F45K22/Release/GLCD.p1: TOOL=CC
#        C:/Users/Pol/Desktop/uni/CI/CI-FIB-main/Lab/L10/Sobre/GLCD.c

# Build tree:
all:	Release

Release:	Release.hex
	cp "Release.hex" "C:/Users/Pol/Desktop/uni/CI/CI-FIB-main/Lab/L10/Sobre/PIC18F45K22.hex"

Release.hex:	main.p1 GLCD.p1 
	$(LD) $(LDFLAGS)  -O"Release.hex" "main.p1" "GLCD.p1"
	rm startup.as
	rm Release.as

main.p1:	../../main.c 
	$(CC) $(CCFLAGS)  -O"main.p1" "../../main.c"

GLCD.p1:	../../GLCD.c 
	$(CC) $(CCFLAGS)  -O"GLCD.p1" "../../GLCD.c"

# tidy - delete all temporary files which are not involved in the target generation
tidy:
	rm -rf Release.hxl
	rm -rf Release.lst
	rm -rf Release.sym
	rm -rf Release.obj
	rm -rf Release.sdb
	rm -rf Release.as
	rm -rf ./startup.obj
	rm -rf ./startup.rlf
	rm -rf ./startup.as
	rm -rf ./startup.lst
	rm -rf ./funclist.
	rm -rf main.pre
	rm -rf main.lst
	rm -rf GLCD.pre
	rm -rf GLCD.lst

# cleanup - delete all generated files
clean:	tidy
	rm -rf Release.hex
	rm -rf main.p1
	rm -rf GLCD.p1
