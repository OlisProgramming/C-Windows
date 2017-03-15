#ifndef PIXELWINDOW_H
#define PIXELWINDOW_H

#include <stdio.h>
#include <windows.h>

typedef COLORREF Colour;

#define COLOUR_1(red, green, blue) RGB((blue) * 255, (green) * 255, (red) * 255)
#define COLOUR_256(red, green, blue) RGB(blue, green, red)

#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 720


#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        
        Colour* m_ScreenImageData;
        HWND m_Hwnd;
        HDC m_Hdc;
    } PixelWindow;
    
    void pxwnd_init(PixelWindow* wnd, HWND hwnd);
    void pxwnd_drawBegin(PixelWindow* wnd);
    void pxwnd_drawEnd(PixelWindow* wnd);
    void pxwnd_setpixel(PixelWindow* wnd, int x, int y, Colour col);
    void pxwnd_setpixel_ind(PixelWindow* wnd, int index, Colour col);
    void pxwnd_close(PixelWindow* wnd);

#ifdef __cplusplus
}
#endif

#endif /* PIXELWINDOW_H */

