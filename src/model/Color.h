#ifndef COLOR_H
#define COLOR_H

struct Color {
    int r;
    int g;
    int b;

    Color(int rValue, int gValue, int bValue) {
        r = rValue;
        g = gValue;
        b = bValue;
    }
};

#endif