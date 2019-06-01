.PHONY: all
all:
	gcc -lm main.c embedded-library/gfx/gfx.c -DDISP_WIDTH=320 -DDISP_HEIGHT=240