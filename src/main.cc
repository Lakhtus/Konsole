#include "app.h"
#include "FensterWindow.h"
#include "GridWindow.h"

class CheckerboardApp : public App {
public:
    CheckerboardApp(int w, int h, const char* title)
        : App(w, h, title), t(0), offsetFactor(4) {
    }
protected:

    bool createWindow() override {
        // window = new FensterWindow(width, height, title);
        window = new GridWindow(width, height, title);
        return window != nullptr;
    }
    void onUpdate() override {
        t++;
        int newMouseX = window->x();
        int newMouseY = window->y();

        if (newMouseX != mouseX || newMouseY != mouseY) {
            LOG_INFO("Mouse at ({}, {})", mouseX, mouseY);
            mouseX = newMouseX;
            mouseY = newMouseY;
        }

    }

    void onRender() override {
        // drawCheckerboard(f, t);
        // window->drawCircle(mouseX, mouseY, 5, RGB(255, 14, 155));
        // window->setPixel(mouseX, mouseY, RGB(255, 14, 155));
        // grid size  72x54
        const int maxW = 71, maxH = 51;
        int w = std::min(window->getWidth(), maxW);
        int h = std::min(window->getHeight(), maxH);



        window->drawCircle(mouseX, mouseY, 10, RGB(255, 0, 0));         // Bright red
        window->drawCircle(25, 25, 7, RGB(0, 0, 255));                  // Bright blue
        window->drawLine(0, 0, w - 1, h - 1, RGB(0, 0, 0));             // Black
        window->drawLine(0, h - 1, w - 1, 0, RGB(0, 0, 0));             // Black

    }

    void onUserInput() override {
        if (window->key(0x1b)) { // ESC
            LOG_WARN("ESC pressed -> quitting");
            running = false;
        }
    }

private:
    int t;
    int mouseX, mouseY;
    int offsetFactor;



    // void drawCheckerboard(Fenster& f, int t, int numScanlines = 9) {  // number of bands
    //     const int S = 16;     // checker size
    //     const int W = width;
    //     const int H = height;
    //     const float PI = 3.14159265358979323846f;

    //     // Fixed channel offsets for chromatic aberration
    //     const int rOffsetX = 2, rOffsetY = 0;
    //     const int gOffsetX = -1, gOffsetY = 1;
    //     const int bOffsetX = 0, bOffsetY = -2;

    //     // Initialize scanlines with random parameters (static keeps them persistent)
    //     static std::vector<Scanline> scanlines;
    //     if (scanlines.empty()) {
    //         for (int i = 0; i < numScanlines; i++) {
    //             Scanline s;
    //             s.speed = 0.3f + (rand() % 100) / 200.0f;   // 0.3 .. 0.8
    //             s.amp = 8.0f + (rand() % 32);             // 8 .. 40
    //             s.width = 10 + (rand() % 30);               // 10 .. 40
    //             s.offset = rand() % H;                      // random vertical start
    //             scanlines.push_back(s);
    //         }
    //     }

    //     for (int y = 0; y < H; y++) {
    //         float influenceTotal = 0.0f;

    //         // Sum up influence from all scanlines
    //         for (auto& s : scanlines) {
    //             float scanY = fmod(t * s.speed + s.offset, (float)H);
    //             float dy = fabsf(y - scanY);

    //             if (dy < s.width / 2.0f) {
    //                 float ratio = 1.0f - (dy / (s.width / 2.0f));
    //                 float influence = 0.5f - 0.5f * cosf(ratio * PI);
    //                 influenceTotal += influence * s.amp;
    //             }
    //         }

    //         int extraNoiseY = (int)influenceTotal;

    //         for (int x = 0; x < W; x++) {
    //             // Base random noise per pixel
    //             int noiseX = (rand() % 3) - 1;
    //             int noiseY = (rand() % 3) - 1;

    //             // Add scanline band distortion
    //             if (extraNoiseY > 0) {
    //                 noiseY += (rand() % (extraNoiseY + 1)) - extraNoiseY / 2;
    //             }

    //             // Chromatic aberration
    //             int r = (((((x + rOffsetX + noiseX) / S) + ((y + rOffsetY + noiseY) / S)) & 1) * 255);
    //             int g = (((((x + gOffsetX + noiseX) / S) + ((y + gOffsetY + noiseY) / S)) & 1) * 255);
    //             int b = (((((x + bOffsetX + noiseX) / S) + ((y + bOffsetY + noiseY) / S)) & 1) * 255);

    //             // add speckle noise
    //             if ((rand() % 100) < 10) { // 2% chance
    //                 r = g = b = rand() % 256;
    //             }

    //             f.px(x, y) = (r << 16) | (g << 8) | b;
    //         }
    //     }
    // }
};

// ---- Entry point ----
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    (void)hInstance, (void)hPrevInstance, (void)pCmdLine, (void)nCmdShow;
    SetConsoleOutputCP(CP_UTF8);
    spdlog::set_level(spdlog::level::trace);
    LOG_TRACE("This is a trace message");
    // TRACE: super detailed—logs every step or value. Use only during deep debugging, NEVER in production.

    LOG_DEBUG("This is a debug message");
    // DEBUG: detailed info useful during development—track variable states, logic paths, etc.

    LOG_INFO("Starting CheckerboardApp");
    // INFO: normal, useful runtime info—like app startup or key milestones. Safe for production.

    LOG_WARN("This is a warning message");
    // WARN: something unexpected happened, but the app still runs. Worth checking later.

    LOG_ERROR("This is an error message");
    // ERROR: something broke or failed, affecting functionality—but the app continues in a degraded state.

    LOG_CRIT("This is a critical message");
    // CRITICAL: something fatal happened—requires immediate attention and usually stops the app.



    CheckerboardApp app(800, 600, "Checkerboard");
    if (!app.create())
        return -1;

    return app.run(60);
}