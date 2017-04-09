#ifndef TUTOR_H
#define TUTOR_H

class Tutor
{
public:

    Tutor();

    ~Tutor();

    virtual void start(int logFrequency) = 0;

    virtual void end() = 0;

};

#endif // TUTOR_H
