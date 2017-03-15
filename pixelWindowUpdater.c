/*
 * OlisProgramming 2017.
 */

#include "pixelWindowUpdater.h"

void wnd_update(double delta, double total, PixelWindow* wnd) {
    
    // Delta = time between two frames
    printf("delta = %fs, total = %fs\n", delta, total);
    pxwnd_drawBegin(wnd);
    pxwnd_setpixel(wnd, 5, 5, COLOUR_1(1,0,1));
    pxwnd_drawEnd(wnd);
}