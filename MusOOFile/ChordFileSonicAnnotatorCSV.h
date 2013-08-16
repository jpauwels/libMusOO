#ifndef ChordFileSonicAnnotatorCSV_h
#define ChordFileSonicAnnotatorCSV_h

//============================================================================
/**
	Class representing a file on disk containing chord segments according to
	syntax used by Matthias Mauch.

	@author		Johan Pauwels
	@date		20110608
*/
//============================================================================
#include <string>
#include <fstream>
#include "MusOOFile/ChordFile.h"

namespace MusOO
{
template <typename ChordLabel>
class ChordFileSonicAnnotatorCSV : public ChordFile
{
public:

	ChordFileSonicAnnotatorCSV(const bool inPitchSpelled);
	ChordFileSonicAnnotatorCSV(std::string inFileName, const bool inPitchSpelled);
	/** Destructor. */
	virtual ~ChordFileSonicAnnotatorCSV();

	virtual void open(const std::string& inFileName);
	virtual void close();

private:

	typedef TimedLabel<ChordLabel> TimedSAChord;
	typedef std::vector<TimedChord> TimedSAChordSequence;

	std::fstream m_File;
	std::string m_FileName;
};
}

template <typename T>
MusOO::ChordFileSonicAnnotatorCSV<T>::ChordFileSonicAnnotatorCSV(const bool inPitchSpelled)
: ChordFile(inPitchSpelled)
{
}

template <typename T>
MusOO::ChordFileSonicAnnotatorCSV<T>::ChordFileSonicAnnotatorCSV(std::string inFileName, const bool inPitchSpelled)
: ChordFile(inPitchSpelled)
{
	open(inFileName);
}

template <typename T>
MusOO::ChordFileSonicAnnotatorCSV<T>::~ChordFileSonicAnnotatorCSV()
{
	close();
}

template <typename T>
void MusOO::ChordFileSonicAnnotatorCSV<T>::open(const std::string& inFileName)
{
	if (m_File.is_open())
	{
		m_File.close();
	}
	m_TimedChords.clear();
	m_FileHasChanged = false;
	m_FileName = inFileName;
	m_File.open(inFileName.c_str(), std::fstream::in);
	if (m_File.is_open())
	{
        std::string theLine;
		while (getline(m_File, theLine))
		{
            std::istringstream theStringStream(theLine);
			TimedLabel<T> theCurTimedChord;
			theStringStream >> theCurTimedChord.onset();
            std::string theLabelString;
			getline(theStringStream,theLabelString,',');
			getline(theStringStream,theLabelString,'"');
			getline(theStringStream,theLabelString,'"');
			theCurTimedChord.label() = T(theLabelString);
			if (!m_TimedChords.empty())
			{
				m_TimedChords.back().offset() = theCurTimedChord.onset();
			}
			m_TimedChords.push_back(theCurTimedChord);
		}
		m_TimedChords.back().offset() = m_TimedChords.back().onset();
	}
    ChordFile::open(inFileName);
}

template <typename T>
void MusOO::ChordFileSonicAnnotatorCSV<T>::close()
{
	if (m_FileHasChanged)
	{
		ChordFile::close();
		TimedSAChordSequence theSAChords(m_TimedChords.begin(), m_TimedChords.end());
		//TODO: implement writing theSAChords to csv file
	}
}

#endif	// #ifndef ChordFileSonicAnnotatorCSV_h
