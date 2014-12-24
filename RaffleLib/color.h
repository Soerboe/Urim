#ifndef COLOR_H
#define COLOR_H

#include <QString>

struct Color {
    Color() {

    }

    bool operator==(const Color& that) {
        return
                this->name == that.name &&
                this->red == that.red &&
                this->blue == that.blue &&
                this->green == that.green;
    }

    QString name;
    int red, green, blue;
};

#endif // COLOR_H
