#ifndef BUTTON_H
#define BUTTON_H

class Button {
    public:
        virtual ~Button() {}
        virtual bool isPressed() = 0;

};

#endif