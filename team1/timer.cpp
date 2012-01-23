#include "timer.h"
 
Timer* Timer::ms_instance = 0;
 
Timer::Timer()
{
    mTimer = new Ogre::Timer();
}
 
Timer::~Timer()
{
    delete mTimer;
}
 
Timer* Timer::getInstance()
{
    if(ms_instance == 0)
        {
            ms_instance = new Timer();
        }
    return ms_instance;
}
 
void Timer::Release()
{
    if(ms_instance)
        {
            delete ms_instance;
        }
    ms_instance = 0;
}
 
void Timer::delay(std::tr1::function<void ()> func, unsigned long time)
{
    TimedCallback cb(getTime() + time, func);
    delay(cb);
}

void Timer::processQueue()
{
    while(!mQueue.empty())
        {
            const TimedCallback &cb = mQueue.top();
            long delta = cb.first - getTime();
            if(delta>0) return;
            cb.second();
            mQueue.pop();
        }
}
 
void Timer::clearQueue()
{
    mQueue = TimedCallbackQueue();
}
