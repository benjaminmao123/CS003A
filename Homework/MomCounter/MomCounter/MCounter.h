#pragma once

class MCounter
{
public:
    MCounter();
    int Add_1();
    int Add_10();
    int Add_100();
    int Add_1000();
    int Reset();
    int Count() const;
    bool Is_Error() const;

private:
    int count;
}; 