/*
 * OlisProgramming 2017.
 */

/* 
 * File:   pixelWindowUpdater.h
 * Author: Oliver
 *
 * Created on 15 March 2017, 18:22
 */

#ifndef PIXELWINDOWUPDATER_H
#define PIXELWINDOWUPDATER_H

#include "pixelwindow.h"

#ifdef __cplusplus
extern "C" {
#endif

    void wnd_update(double delta, double total, PixelWindow* wnd);

#ifdef __cplusplus
}
#endif

#endif /* PIXELWINDOWUPDATER_H */

