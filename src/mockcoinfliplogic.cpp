#include "coinfliplogic.h"
#include "timer.h"
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

Side CoinFlipLogic::flip()
{
    Side side = Tails;
    std::string result = *it;
    if (result.compare("head") == 0) {
        side = Heads;
    }
    
    // advance iterator
    ++it;
    if (it == end) {
        it = begin;
    }
    return side;
}
