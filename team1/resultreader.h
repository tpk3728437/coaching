#ifndef RESULTREADER_H
#define RESULTREADER_H

#include <istream>
#include <vector>

typedef std::vector<std::string> StringList;


class ResultReader
{
public:
    ResultReader(std::istream& stream);    
    StringList results() const;

private:
    StringList mResults;
};

#endif // RESULTREADER_H
