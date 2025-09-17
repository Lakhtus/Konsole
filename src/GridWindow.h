#ifndef GRIDWINDOW_H
#define GRIDWINDOW_H

#include "window.h"
#include "Fenster.h"

class GridWindow : public Window {
public:
    GridWindow(int w, int h, const char* title,
        int cellWidth = 10, int cellHeight = 10,
        int gapX = 1, int gapY = 1,
        uint32_t clear_color = RGB(0, 0, 0)) {
        this->height = h;
        this->width = w;
        this->title = (char*)title;
        this->clear_color = clear_color;
        this->cellWidth = cellWidth;
        this->cellHeight = cellHeight;
        this->gapX = gapX;
        this->gapY = gapY;

        f = new Fenster(w, h, title);

        // --- Fit cells within window, ignore remainder ---
        gx = (width + gapX) / (cellWidth + gapX);
        gy = (height + gapY) / (cellHeight + gapY);

        if (gx < 1) gx = 1;
        if (gy < 1) gy = 1;

        // --- Compute "usable area" ---
        usedWidth = gx * cellWidth + (gx - 1) * gapX;
        usedHeight = gy * cellHeight + (gy - 1) * gapY;

        // Padding = leftover space on right/bottom
        padX = width - usedWidth;
        padY = height - usedHeight;

        LOG_DEBUG("GridWindow: {}x{} cells of {}x{} + gap {}x{}, usable {}x{}, padding {}x{}",
            gx, gy, cellWidth, cellHeight, gapX, gapY, usedWidth, usedHeight, padX, padY);

        // --- Allocate grid ---
        grid = new uint32_t[gx * gy];
        for (int i = 0; i < gx * gy; i++) {
            grid[i] = RGB(255, 255, 255); // default white
        }
    }

    ~GridWindow() {
        delete f;
        delete[] grid;
    }

    void display() override {

        // Draw cells
        for (int y = 0; y < gy; y++) {
            for (int x = 0; x < gx; x++) {
                uint32_t color = grid[y * gx + x];

                int startX = x * (cellWidth + gapX);
                int startY = y * (cellHeight + gapY);

                // Clip drawing if padding remains
                if (startX + cellWidth > width)  continue;
                if (startY + cellHeight > height) continue;

                for (int j = 0; j < cellHeight; j++) {
                    for (int i = 0; i < cellWidth; i++) {
                        f->px(startX + i, startY + j) = color;
                    }
                }
            }
        }
    }


    void clear() override {
        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++)
                f->px(x, y) = clear_color;

        for (int i = 0; i < gx * gy; i++)
            grid[i] = RGB(255, 255, 255);
    }

    void setPixel(int x, int y, uint32_t color) override {
        if (x < 0 || x >= gx || y < 0 || y >= gy) return;
        grid[y * gx + x] = color;
    }

    bool key(int key) override { return f->key(key); }
    bool loop(int fps) override { return f->loop(fps); }

    int x() override {
        int tmp = f->x() / (cellWidth + gapX);
        if (tmp < 0) return 0;
        if (tmp >= gx) return gx - 1;
        return tmp;
    }
    int y() override {
        int tmp = f->y() / (cellHeight + gapY);
        if (tmp < 0) return 0;
        if (tmp >= gy) return gy - 1;
        return tmp;
    }

    int getBoundryX() override { return gx; }
    int getBoundryY() override { return gy; }

private:
    Fenster* f;
    int gx, gy;
    uint32_t* grid;

    int cellWidth;
    int cellHeight;
    int gapX, gapY;

    int usedWidth, usedHeight; // exact area covered by grid
    int padX, padY;            // padding (unused space at right/bottom)
};

#endif
