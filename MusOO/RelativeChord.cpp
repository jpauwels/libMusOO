//============================================================================
/**
	Implementation file for RelativeChord.h

	@author		Johan Pauwels
	@date		20101222
*/
//============================================================================

// Includes
#include <sstream>
#include <stdexcept>
#include "RelativeChord.h"
#include "QMChord.h"

using std::string;
using std::ostringstream;

const RelativeChord& RelativeChord::silence()
{
	static const RelativeChord silence(Interval::silence(), ChordType::none());
	return silence;
}

const RelativeChord& RelativeChord::none()
{
	static const RelativeChord none(Interval::none(), ChordType::none());
	return none;
}

const RelativeChord& RelativeChord::unknown()
{
	static const RelativeChord unknown(Interval::unknown(), ChordType::none());
	return unknown;
}

RelativeChord::RelativeChord()
: m_RootInterval(Interval::unknown()), m_Type(ChordType::none())
{
}

RelativeChord::RelativeChord(const Interval& inRootInterval, const ChordType& inType)
: m_RootInterval(inRootInterval), m_Type(inType)
{
}

RelativeChord::RelativeChord(const Key& inKey, const Chord& inChord)
: m_RootInterval(inKey.tonic(), inChord.root()), m_Type(inChord.type())
{
	if (inChord == Chord::silence())
	{
		*this = silence();
	}
	else if (inChord == Chord::noChord())
	{
		*this = none();
	}
	else if (inChord == Chord::unknown())
	{
		*this = unknown();
	}
	if (inKey == Key::silence())
	{
		std::runtime_error("Cannot deduce relative chord when key is silence");
	}
}

RelativeChord::RelativeChord( const std::string& inDegree, const ChordType& inChordType, const Mode& inMode )
	: m_RootInterval(inDegree, inMode), m_Type(inChordType)
{
}

/*
RelativeChord::RelativeChord( const RelativeChord& inRelativeChord )
	: m_RootInterval(inRelativeChord.m_RootInterval), m_Type(inRelativeChord.m_Type)
{
}*/

RelativeChord::~RelativeChord()
{
	// Nothing to do...
}

bool RelativeChord::operator==(const RelativeChord& inRelativeChord) const
{
	return m_RootInterval == inRelativeChord.m_RootInterval && m_Type == inRelativeChord.m_Type;
}

bool RelativeChord::operator!=(const RelativeChord& inRelativeChord) const
{
	return m_RootInterval != inRelativeChord.m_RootInterval || m_Type != inRelativeChord.m_Type;
}

bool RelativeChord::operator<(const RelativeChord& inRelativeChord) const
{
	if (m_RootInterval != inRelativeChord.m_RootInterval)
	{
		return m_RootInterval < inRelativeChord.m_RootInterval;
	}
	else
	{
		return m_Type < inRelativeChord.m_Type;
	}
}

RelativeChord& RelativeChord::operator=(const RelativeChord& inRelativeChord)
{
	m_RootInterval = inRelativeChord.m_RootInterval;
	m_Type = inRelativeChord.m_Type;
	return *this;
}

const std::string RelativeChord::asDegree(const Mode& inMode) const
{
	if (*this == RelativeChord::unknown())
	{
		return "X";
	}
	else if (*this == RelativeChord::none())
	{
		return "N";
	}
	else if (*this == RelativeChord::silence())
	{
		return "S";
	}
	else
	{
		return m_RootInterval.asDegree(inMode) + ":" + QMChordType(m_Type).str();
	}
}

/*const std::string RelativeChord::str() const
{
	if (*this == RelativeChord::unknown())
	{
		return "X";
	}
	else if (*this == RelativeChord::none())
	{
		return "N";
	}
	else if (*this == RelativeChord::silence())
	{
		return "S";
	}
	ostringstream theStringStream;
	theStringStream << m_RootInterval.str() << ":" << QMChordType(m_Type).str();
	return theStringStream.str();
}*/

const Interval& RelativeChord::rootInterval() const
{
	return m_RootInterval;
}

const ChordType& RelativeChord::type() const
{
	return m_Type;
}


QMRelativeChord::QMRelativeChord()
{
}

QMRelativeChord::QMRelativeChord(const std::string& inString, const Mode inMode)
{
	if (!inString.compare(0,1,"S"))
	{
		// Silence
		*this = RelativeChord::silence();
	}
	else if (!inString.compare(0,1,"N"))
	{
		// No-chord
		*this = RelativeChord::none();
	}
	else
	{
		//find colon which separates root and type
		size_t theColon = inString.find(":");
		size_t theSlash = inString.find("/");
		string theRootDegree = inString.substr(0,std::min(theColon, theSlash));
		QMChordType theType;

		if (theColon != string::npos)
		{
			//explicit type, optional slash
			theType = QMChordType(inString.substr(theColon+1));
		}
		else
		{
			if (theSlash == string::npos)
			{
				//no explicit type, no slash
				theType = ChordType::major();
			}
			else
			{
				//no explicit type, with slash
				theType = QMChordType("maj"+inString.substr(theSlash));
			}
		}
		*this = RelativeChord(theRootDegree, theType, inMode);
	}
}

QMRelativeChord::QMRelativeChord(const RelativeChord& inRelativeChord)
	: RelativeChord(inRelativeChord)
{
}
