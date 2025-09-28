#include "helpers.h"
#ifndef WINDOW_H
#define WINDOW_H

class Window {
public:
    virtual ~Window() {};
    virtual void clear() = 0;
    virtual void display() = 0;
    virtual void setPixel(int x, int y, uint32_t color) = 0;
    virtual bool key(int key) = 0;
    virtual bool loop(int fps) = 0;



    const int getHeight() {
        return height;
    }
    bool setHeight(int h) {
        height = h;
        return true;
    }

    const int getWidth() {
        return width;
    }
    bool setWidth(int w) {
        width = w;
        return true;
    }

    const char* getTitle() {
        return title;
    }
    bool setTitle(const char* t) {
        title = (char*)t;
        return true;
    }

    uint32_t getClearColor() {
        return clear_color;
    }

    bool setClearColor(uint32_t c) {
        clear_color = c;
        return true;
    }
    virtual int getBoundryX() = 0;
    virtual int getBoundryY() = 0;

    virtual int x() = 0;
    virtual int y() = 0;


    void drawCircle(int centerX, int centerY, int radius, uint32_t color) {
        /*Write a function that takes window f, a center x, y, and radius and color
        Then draw a circle centered at x, y, with radius r, and color
        f.px(x, y) = color to set  a color to the pixel x y
        to use a loop

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                f.px(x, y) = color;
            }
        }
         */

        for (int y = floor(centerY - radius); y <= ceil(centerY + radius); y++) {
            if (y < 0 || y >= getBoundryY()) {
                continue;
            }

            for (int x = floor(centerX - radius); x <= ceil(centerX + radius); x++) {

                // pixel working on is (x, y)
                if (x < 0 || x >= getBoundryX()) {
                    continue;
                }

                if (sqrt(pow(x - centerX, 2) + pow(y - centerY, 2)) <= radius) {
                    setPixel(x, y, color);
                }


            }
        }
    }

    void drawLine(int x1, int y1, int x2, int y2, uint32_t color) {
        int steps = 0;
        float dx = abs(x2-x1); float dy = abs(y2-y1);
        int xi = 0 ; int yi = 0 ;


        if (dx>dy) {
            steps = dx ;
        }else {
            steps = dy;
        }

        
        for (int i = 0; i <= steps; i++){
            xi = x1 + round(dx/steps * i) ;
            yi = y1 + round(dy/steps * i) ;
            
            setPixel(xi, yi, color);

        }

    }





protected:
    char* title;
    int height;
    int width;
    uint32_t clear_color;
    int mouseX = 0, mouseY = 0;
};

#endif