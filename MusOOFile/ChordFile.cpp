//============================================================================
/**
	Implementation file for ChordFile.h
	
	@author		Johan Pauwels
	@date		20090119
*/
//============================================================================

// Includes
#include "ChordFile.h"

ChordFile::ChordFile(const bool inPitchSpelled) 
: m_FileHasChanged(false), m_PitchSpelled(inPitchSpelled)
{
}

ChordFile::~ChordFile()
{
}

const TimedChordSequence& ChordFile::readAll()
{
	return m_TimedChords;
}

const TimedChordSequence ChordFile::readRange(double inStartTime, double inEndTime)
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
	TimedChordSequence::const_iterator it = m_TimedChords.begin();
	while (it != m_TimedChords.end() && it->offset() <= inStartTime)
	{
		++it;
	}
	//add range
	TimedChordSequence theChordsRange;
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

void ChordFile::writeAll(TimedChordSequence& inTimedChords)
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
    if (!m_PitchSpelled)
    {
        for (TimedChordSequence::iterator it = m_TimedChords.begin(); it != m_TimedChords.end(); ++it)
        {
//            it->label() = it->label().ignoreSpelling();
        }
    }
}

void ChordFile::close()
{
	const TimedChordSequence theTimedChords = m_TimedChords;
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
