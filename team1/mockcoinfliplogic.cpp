#include "coinfliplogic.h"
#include "timer.h"
#include <boost/function.hpp>
#include "resultreader.h"

static StringList RESULTS;
static StringList::iterator it;
static StringList::iterator begin;
static StringList::iterator end;

CoinFlipLogic::CoinFlipLogic() :
    mCoinFlipResultCallback(0)
{
    // open and read the file to a string
    std::ifstream inputfile("results", std::ifstream::in);
    ResultReader reader(inputfile);
    RESULTS = reader.results();
    it = RESULTS.begin();
    begin = RESULTS.begin();
    end = RESULTS.end();
}

CoinFlipLogic::~CoinFlipLogic()
{
}

void CoinFlipLogic::Flip(FlipResult& result)
{
    // save the interface
    mCoinFlipResultCallback = &result;
    
    boost::function<void ()> callback(boost::bind(&CoinFlipLogic::onCoinFlippedTimerElapse, this));
    
    ::Timer::getInstance()->delay(callback, 1000);
}

void CoinFlipLogic::onCoinFlippedTimerElapse() 
{ 
    std::string result = *it;
    if (result.compare("head") == 0) {
    mCoinFlipResultCallback->flipResult(Heads);
    } else {
    mCoinFlipResultCallback->flipResult(Tails);
    }
    
    // advance iterator
    ++it;
    if (it == end) {
        it = begin;
    }
}
