#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <iostream>

void drawTriangle() {
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0); // Merah
    glVertex2f(-0.5, -0.5);

    glColor3f(0.0, 1.0, 0.0); // Hijau
    glVertex2f(0.5, -0.5);

    glColor3f(0.0, 0.0, 1.0); // Biru
    glVertex2f(0.0, 0.5);
    glEnd();
}

int main() {
    Display* display = XOpenDisplay(NULL);
    if (!display) {
        std::cerr << "Failed to open X display\n";
        return -1;
    }

    Window root = DefaultRootWindow(display);

    GLint attributes[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};
    XVisualInfo* vi = glXChooseVisual(display, 0, attributes);
    if (!vi) {
        std::cerr << "No appropriate visual found\n";
        return -1;
    }

    Colormap cmap = XCreateColormap(display, root, vi->visual, AllocNone); 
    XSetWindowAttributes swa;
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask;

    Window win = XCreateWindow(display, root, 0, 0, 800, 600, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
    XMapWindow(display, win);

    GLXContext glc = glXCreateContext(display, vi, NULL, GL_TRUE);
    glXMakeCurrent(display, win, glc);

    glClearColor(0.0, 0.0, 0.0, 1.0); // Warna background
    glViewport(0, 0, 800, 600); // Ukuran window

    while (true) {
        XEvent xev;
        XNextEvent(display, &xev);
        if (xev.type == Expose) {
            glClear(GL_COLOR_BUFFER_BIT);
            drawTriangle();
            glXSwapBuffers(display, win);
        } else if (xev.type == KeyPress) {
            break;
        }
    }

    glXMakeCurrent(display, None, NULL);
    glXDestroyContext(display, glc);
    XDestroyWindow(display, win);
    XCloseDisplay(display);

    return 0;
}
