#ifndef __BUTTON_H__
#define __BUTTON_H__

class Button {
    public:
        virtual ~Button() {}
        virtual bool isPressed() = 0;

};

#endif