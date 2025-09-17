#include "FensterWindow.h"
#include "window.h"
#define _USE_MATH_DEFINES // Required on some systems (e.g., Windows with MSVC)

#include <cmath>
#include <mutex>          // ✅ Add this
#include "helpers.h"

struct Scanline {
    float speed;   // movement speed
    float amp;     // distortion amplitude
    int width;     // band thickness
    float offset;  // vertical offset (random start)
};

// ---- Base App class ----
class App {
public:
    App(int w, int h, const char* title)
        : width(w), height(h), title(title), window(nullptr), running(false) {
    }

    virtual ~App() {
        destroy();
    }

    virtual bool createWindow() = 0;

    bool create() {
        init_logging();

        LOG_INFO("Creating window {}x{} [{}]", width, height, title);
        // window = new FensterWindow(width, height, title);
        createWindow();

        running = (window != nullptr);

        if (!running) {
            LOG_ERROR("Failed to create Fenster window");
            return false;
        }

        return true;
    }

    void destroy() {
        if (window) {
            LOG_INFO("Destroying app");
            delete window;
            window = nullptr;
        }
        spdlog::shutdown();
    }


    int run(int fps = 60) {
        if (!window) {
            LOG_ERROR("App not created before run()");
            return -1;
        }

        LOG_INFO("App starting main loop");
        while (running && window->loop(fps)) {
            window->clear();
            onUserInput();
            onUpdate();
            onRender();
            window->display();
        }
        LOG_INFO("App loop ended");
        return 0;
    }

protected:
    // User must override these
    virtual void onUpdate() = 0;
    virtual void onRender() = 0;
    virtual void onUserInput() = 0;

    Window* window;
    int width, height;
    const char* title;
    bool running;

private:
    void init_logging() {
        try {

            spdlog::set_level(spdlog::level::debug);
            // spdlog::flush_on(spdlog::level::warn);
            // spdlog::set_pattern("[%H:%M:%S.%e] [%^%l%$] [%n] %v");

            LOG_INFO("Logging initialized ✅");
        } catch (const spdlog::spdlog_ex& ex) {
            printf("Log init failed: %s\n", ex.what());
        }
    }

};
