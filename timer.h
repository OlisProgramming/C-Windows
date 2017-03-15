/*
 * OlisProgramming 2017.
 */

/* 
 * File:   timer.h
 * Author: Oliver
 *
 * Created on 15 March 2017, 18:50
 */

#ifndef TIMER_H
#define TIMER_H

#ifdef __cplusplus
extern "C" {
#endif
    
    #include <windows.h>
    
    typedef struct {
        LARGE_INTEGER start;
        LARGE_INTEGER freq;
        LARGE_INTEGER elapsed_ms;
        double elapsed;
    } Timer;
    
    Timer timer_create() {
        Timer t;
        QueryPerformanceCounter(&(t.start));
        QueryPerformanceFrequency(&(t.freq)); 
        t.elapsed = 0.0;
        return t;
    }
    
    void timer_reset(Timer* timer) {
        QueryPerformanceCounter(&(timer->start));
    }

    double timer_tick(Timer* timer) {
        LARGE_INTEGER end;
        QueryPerformanceCounter(&end);
        timer->elapsed_ms.QuadPart = end.QuadPart - timer->start.QuadPart;
        timer->elapsed = (timer->elapsed_ms.QuadPart * 1000000) / timer->freq.QuadPart / 1000000.0;
        timer->start = end;
        return timer->elapsed;
    }
    
    double timer_get_total(Timer* timer) {
        LARGE_INTEGER end;
        QueryPerformanceCounter(&end);
        timer->elapsed_ms.QuadPart = end.QuadPart - timer->start.QuadPart;
        timer->elapsed = (timer->elapsed_ms.QuadPart * 1000000) / timer->freq.QuadPart / 1000000.0;
        return timer->elapsed;
    }
    
#ifdef __cplusplus
}
#endif

#endif /* TIMER_H */

