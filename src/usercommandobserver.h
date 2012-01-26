#ifndef USERCOMMANDOBSERVER_H
#define USERCOMMANDOBSERVER_H

/**
 * A high-level user command callback interface.
 */
class UserCommandObserver
{
public:
    virtual void quitButtonPressed() =0;
    virtual void playButtonPressed() =0;
    virtual void doubleUpButtonPressed() =0;
    virtual void payoutButtonPressed() =0;
protected:
    virtual ~UserCommandObserver() {}
};

#endif // USERCOMMANDOBSERVER_H
