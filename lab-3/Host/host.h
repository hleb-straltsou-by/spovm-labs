#ifndef HOST_H
#define HOST_H

class Host
{

public:

    Host();

    ~Host();

    virtual void createStudent() = 0;

    virtual void createStudentWithPeriod(int period) = 0;

    virtual void createTutor(int logFrequency) = 0;

    virtual void listenUserCommand() = 0;
};

#endif // HOST_H
