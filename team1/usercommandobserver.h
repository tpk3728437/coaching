#ifndef USERCOMMANDOBSERVER_H
#define USERCOMMANDOBSERVER_H

/**
 * A high-level user command callback interface.
 */
class UserCommandObserver
{
public:
    virtual void QuitButtonPressed() =0;
    virtual void PlayButtonPressed() =0;
    virtual void DoubleUpButtonPressed() =0;
    virtual void PayoutButtonPressed() =0;
protected:
    virtual ~UserCommandObserver() {}
};

#endif // USERCOMMANDOBSERVER_H
