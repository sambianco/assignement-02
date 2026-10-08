#ifndef __SERVOMOTOR_H__
#define __SERVOMOTOR_H__

class ServoMotor {
    public:
        virtual ~ServoMotor() {}
        virtual void attach() = 0;
        virtual void detach() = 0;
        virtual void setAngle(int angle) = 0;
        virtual int getAngle() = 0;
};

#endif