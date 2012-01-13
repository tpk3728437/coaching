#include "resultreader.h"
#include <iterator>
#include <iostream>

/**
 * EBNF: 
 * input = token , {separator input}*
 * token = 'head' | 'tail'
 * separator = '\n'
 */
ResultReader::ResultReader(std::istream& stream)
{
    std::istream_iterator<std::string> begin(stream);
    std::istream_iterator<std::string> eos;
    
    std::copy(begin, eos, back_inserter(mResults));    
}
    
StringList ResultReader::results() const
{
    return mResults;
}

