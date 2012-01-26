#ifndef TIMER_H
#define TIMER_H
 
#include <OGRE/OgreTimer.h>
#include <vector>
#include <queue>
#include <utility>
#include <tr1/functional>

 
typedef std::pair< unsigned long, std::tr1::function<void ()> > TimedCallback;
 
class PrioritizeCallbacks
{
public:
    bool operator() ( const TimedCallback& lhs, const TimedCallback& rhs ) const
    {
        return rhs.first < lhs.first;
    }
};
 
typedef std::priority_queue< TimedCallback, std::vector<TimedCallback>, PrioritizeCallbacks > TimedCallbackQueue;
 
class Timer
{
public:
    static Timer* getInstance();
    static void release();
 
    /**
     * \return Milliseconds since timer started
     */
    unsigned long getTime() { return mTimer->getMilliseconds(); }
 
    /**
     * \return Microseconds since timer started
     */
    unsigned long getMicroTime() { return mTimer->getMicroseconds(); }
 
    /**
     * \brief Delayed execution of a callback
     * \param cb
     */
    inline void delay(TimedCallback cb) { mQueue.push(cb); }
 
    /**
     * \brief Delayed execution of a callback
     * \param func the callback to execute
     * \param time to delay execution of callback
     */
    void delay(std::tr1::function<void ()> func, unsigned long time);
 
    /**
     * \brief Process the callback queue, executes pending functions
     * \note Have to call this manually, at shortest possible intervals,
     * If using Ogre::Root::startRendering() for example, this would be on every
     * onFrameStarted().
     */
    void processQueue();
 
    /**
     * \brief Clears the queue
     */
    void clearQueue();
 
private:
    Timer();
    virtual ~Timer();
 
protected:
    Ogre::Timer* mTimer;
 
    TimedCallbackQueue mQueue;
 
    static Timer* ms_instance;
};
 
#endif // TIMER_H
