#ifndef FENSTER_WINDOW_H
#define FENSTER_WINDOW_H
#include "window.h"
#include "fenster.h"

class FensterWindow : public Window {
public:
    FensterWindow(int w, int h, const char* title, uint32_t clear_color = RGB(0, 0, 0)) {
        this->height = h;
        this->width = w;
        this->title = (char*)title;
        this->clear_color = clear_color;

        f = new Fenster(w, h, title);
    }

    ~FensterWindow() override {
        delete f;
        f = nullptr;
    }

    void clear() override {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                f->px(x, y) = clear_color;
            }
        }
    }

    void display() override {
        // Fenster handles display internally in its loop method
    }
    bool loop(int fps) override {
        return f->loop(fps);
    }
    void setPixel(int x, int y, uint32_t color) override {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            f->px(x, y) = color;
        }
    }
    bool key(int key) override {
        return f->key(key);
    }

    int x() override {
        return f->x();
    }
    int y() override {
        return f->y();
    }
    int getBoundryX() override {
        return width;
    }
    int getBoundryY() override {
        return height;
    }




private:
    Fenster* f;


};

#endif