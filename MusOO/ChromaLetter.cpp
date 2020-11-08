
#include "MusOO/ChromaLetter.h"
#include <cmath>
#include <stdexcept>

using std::map;
using std::string;
using std::pair;
using namespace MusOO;


static const pair<char,ptrdiff_t> theNameToLinePosition[] = {pair<char,ptrdiff_t>('A',5), pair<char,ptrdiff_t>('B',7),
    pair<char,ptrdiff_t>('C',2), pair<char,ptrdiff_t>('D',4), pair<char,ptrdiff_t>('E',6), pair<char,ptrdiff_t>('F',1),
    pair<char,ptrdiff_t>('G',3), pair<char,ptrdiff_t>('N',std::numeric_limits<ptrdiff_t>::max()-1)};
const map<char,ptrdiff_t> ChromaLetter::s_NameToLinePosition(theNameToLinePosition, theNameToLinePosition+8);

static const pair<ptrdiff_t,char> theLinePositionToName[] = {pair<ptrdiff_t,char>(1,'F'), pair<ptrdiff_t,char>(2,'C'),
    pair<ptrdiff_t,char>(3,'G'), pair<ptrdiff_t,char>(4,'D'), pair<ptrdiff_t,char>(5,'A'), pair<ptrdiff_t,char>(6,'E'),
    pair<ptrdiff_t,char>(7,'B')};
const map<ptrdiff_t,char> ChromaLetter::s_LinePositionToName(theLinePositionToName, theLinePositionToName+7);

ChromaLetter::ChromaLetter(const std::string& inName)
{
    if (inName.empty())
    {
        throw std::invalid_argument("Empty note name");
    }
    else if (inName.find_first_not_of("s#bABCDEFGN") != string::npos)
    {
        throw std::invalid_argument("Illegal input '" + inName + "' for a chroma name");
    }
    //convert base note
    m_LinePosition = s_NameToLinePosition.find(inName[0])->second;
    //convert modifier
    m_LinePosition += stringModifierToCircleSteps(inName.substr(1));
    m_HasSpelling = true;
}

const std::string ChromaLetter::str() const
{
    if (*this == silence())
    {
        return "S";
    }
    else if (*this == none())
    {
        return "N";
    }
    else if (*this == undefined())
    {
        return "X";
    }
    //limit the position on the circle to the allowed basic range by adding modifiers
    ptrdiff_t theRangeLimitedLinePosition = m_LinePosition;
    string theModifierString = "";
    while (theRangeLimitedLinePosition < s_LinePositionToName.begin()->first)
    {
        theModifierString.append("b");
        theRangeLimitedLinePosition += 7;
    }
    while (s_LinePositionToName.lower_bound(theRangeLimitedLinePosition) == s_LinePositionToName.end())
    {
        theModifierString.append("#");
        theRangeLimitedLinePosition -= 7;
    }
    //convert the range-limited circle position to the basic note string
    return s_LinePositionToName.find(theRangeLimitedLinePosition)->second + theModifierString;
}
