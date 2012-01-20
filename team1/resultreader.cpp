#include "resultreader.h"
#include <iterator>
#include <iostream>
#include <boost/iterator/filter_iterator.hpp>

/**
 * EBNF: 
 * input = token , {separator token}*
 * token = 'head' | 'tail'
 * separator = '\n'
 */

struct isHeadOrTail
{
	bool operator()(const std::string& input) const {
		const bool head = input.compare("head") == 0;
		const bool tail = input.compare("tail") == 0;
		return head || tail;
	}
};

ResultReader::ResultReader(std::istream& stream)
{
    typedef boost::filter_iterator<isHeadOrTail, std::istream_iterator<std::string> > FilterIterator;

    FilterIterator begin(stream);
    FilterIterator eos;

    std::copy(begin, eos, back_inserter(mResults));
}
    
StringList ResultReader::results() const
{
    return mResults;
}

