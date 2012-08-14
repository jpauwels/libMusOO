//============================================================================
/**
	Implementation file for ChordFile.h
	
	@author		Johan Pauwels
	@date		20090119
*/
//============================================================================

// Includes
#include "ChordFile.h"

ChordFile::ChordFile() 
: m_FileHasChanged(false)
{
}

ChordFile::~ChordFile()
{
}

const ChordSequence& ChordFile::readAll()
{
	return m_TimedChords;
}

const ChordSequence ChordFile::readRange(double inStartTime, double inEndTime)
{
	//range check
	if (!m_TimedChords.empty() && inStartTime < m_TimedChords.front().onset())
	{
		inStartTime = m_TimedChords.front().onset();
	}
	if (inEndTime <= inStartTime || (!m_TimedChords.empty() && inEndTime > m_TimedChords.back().offset()))
	{
		inEndTime = m_TimedChords.back().offset();
	}
	//find first label in range
	ChordSequence::const_iterator it = m_TimedChords.begin();
	while (it != m_TimedChords.end() && it->offset() <= inStartTime)
	{
		++it;
	}
	//add range
	ChordSequence theChordsRange;
	while (it != m_TimedChords.end() && it->onset() < inEndTime)
	{
		theChordsRange.push_back(*it);
		++it;
	}
	//update times of extrema
	if (!theChordsRange.empty())
	{
		theChordsRange.front().onset() = inStartTime;
		theChordsRange.back().offset() = inEndTime;
	}
	return theChordsRange;
}

void ChordFile::writeAll(ChordSequence& inTimedChords)
{
	m_TimedChords = inTimedChords;
	m_FileHasChanged = true;
}

bool ChordFile::isEmpty() const
{
	return m_TimedChords.empty();
}


void ChordFile::open(const std::string& inFileName)
{
}

void ChordFile::close()
{
	const ChordSequence theTimedChords = m_TimedChords;
	m_TimedChords.clear();
	// add silence at beginning if necessary
	if (!theTimedChords.empty())
	{
		if (theTimedChords.front().onset() > 0.)
		{
			m_TimedChords.push_back(TimedChord(0., theTimedChords.front().onset(), Chord::silence()));
		}
		m_TimedChords.push_back(theTimedChords.front());
	}
	for (size_t i = 1; i < theTimedChords.size(); ++i)
	{
		// make implicit no-chords explicit
		if (theTimedChords[i-1].offset() < theTimedChords[i].onset())
		{
			m_TimedChords.push_back(TimedChord(theTimedChords[i-1].offset(), 
				theTimedChords[i].onset(), Chord::silence()));
		}
		m_TimedChords.push_back(theTimedChords[i]);
	}
}
