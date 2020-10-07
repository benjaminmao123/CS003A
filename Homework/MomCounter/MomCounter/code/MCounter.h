#pragma once

class MCounter
{
public:
    /*
        Constructor to initialize properties.
        Sets count to 0 and specifies a value for maxCount.

        @param <const int &maxCount>: The max count allowed
            before overflow.
    */
    MCounter(int maxCount);

    //Adds 1 the counter.
    int Add_1();

    //Adds 10 to the counter.
    int Add_10();

    //Adds 100 to the counter.
    int Add_100();

    //Adds 1000 to the counter.
    int Add_1000();

    //Resets the counter to 0.
    int Reset();

    //Returns the current count.
    int Count() const;

    //Checks if the count has overflowed.
    bool Is_Error() const;

private:
    int count;
    int maxCount;
}; 