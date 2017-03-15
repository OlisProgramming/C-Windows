
#include "pixelwindow.h"

void pxwnd_init(PixelWindow* wnd, HWND hwnd) {

    wnd->m_Hwnd = hwnd;
    
    wnd->m_ScreenImageData = (Colour*)calloc(SCREEN_WIDTH * SCREEN_HEIGHT, sizeof(Colour));
    /* Filling array here */
    /*
    m_ScreenImageData[0] = RGB(255, 0, 255);
    m_ScreenImageData[1] = RGB(255, 0, 255);
    m_ScreenImageData[2] = RGB(255, 0, 255);
    m_ScreenImageData[3] = RGB(255, 0, 255);
    */

    //////

    /*pxwnd_drawBegin(wnd);
    for (unsigned i = 0; i < OS_SCREEN_WIDTH; ++i)
            for (unsigned j = 0; j < OS_SCREEN_HEIGHT; ++j)
                    pxwnd_setpixel(wnd, i, j, COLOUR_1(i / (float)SCREEN_WIDTH, j / (float)SCREEN_HEIGHT, 1));
    pxwnd_drawEnd(wnd);*/
}

void pxwnd_drawBegin(PixelWindow* wnd) {
    wnd->m_Hdc = GetDC(wnd->m_Hwnd);
}

void pxwnd_drawEnd(PixelWindow* wnd) {
    // Creating temp bitmap
    HBITMAP map = CreateBitmap(SCREEN_WIDTH, // width. 512 in my case
            SCREEN_HEIGHT, // height
            1, // Colour Planes, unfortunately don't know what is it actually. Let it be 1
            8 * 4, // Size of memory for one pixel in bits (in win32 4 bytes = 4*8 bits)
            (void*)wnd->m_ScreenImageData); // pointer to array
                                                               // Temp HDC to copy picture
    HDC src = CreateCompatibleDC(wnd->m_Hdc); // HDC - Device context for window, I've got earlier with GetDC(hWnd) or GetDC(NULL);
    SelectObject(src, map); // Inserting picture into our temp HDC
                                                    // Copy image from temp HDC to window
    BitBlt(wnd->m_Hdc, // Destination
            0,  // x and
            0,  // y - upper-left corner of place, where we'd like to copy
            SCREEN_WIDTH, // width of the region
            SCREEN_HEIGHT, // height
            src, // source
            0,   // x and
            0,   // y of upper left corner  of part of the source, from where we'd like to copy
            SRCCOPY); // Defined DWORD to just copy pixels. Watch more on MSDN;

    DeleteDC(src); // Deleting temp HDC
    ReleaseDC(wnd->m_Hwnd, wnd->m_Hdc);
}

void pxwnd_setpixel(PixelWindow* wnd, int x, int y, Colour col) {
    wnd->m_ScreenImageData[x + y*SCREEN_WIDTH] = col;
    //printf("X = %d, Y = %d: Pixel = %d\n", x, y, x + y*SCREEN_WIDTH);
}

void pxwnd_setpixel_ind(PixelWindow* wnd, int index, Colour col) {
    wnd->m_ScreenImageData[index] = col;
    //printf("X = %d, Y = %d: Pixel = %d\n", x, y, x + y*SCREEN_WIDTH);
}

void pxwnd_close(PixelWindow* wnd) {
    CloseWindow(wnd->m_Hwnd);
}