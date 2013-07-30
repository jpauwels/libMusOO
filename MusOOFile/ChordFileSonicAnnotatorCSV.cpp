//============================================================================
/**
	Implementation file for ChordFileSonicAnnotatorCSV.h
	
	@author		Johan Pauwels
	@date		20110608
*/
//============================================================================

// Guard against multiple template implementation inclusions
#ifndef ChordFileSonicAnnotatorCSV_cpp
#define ChordFileSonicAnnotatorCSV_cpp

// Includes
#include <sstream>
#include "ChordFileSonicAnnotatorCSV.h"

using std::string;
using std::istringstream;

template <typename T>
ChordFileSonicAnnotatorCSV<T>::ChordFileSonicAnnotatorCSV(const bool inPitchSpelled)
: ChordFile(inPitchSpelled)
{
}

template <typename T>
ChordFileSonicAnnotatorCSV<T>::ChordFileSonicAnnotatorCSV(std::string inFileName, const bool inPitchSpelled)
: ChordFile(inPitchSpelled)
{
	open(inFileName);
}

template <typename T>
ChordFileSonicAnnotatorCSV<T>::~ChordFileSonicAnnotatorCSV()
{
	close();
}

template <typename T>
void ChordFileSonicAnnotatorCSV<T>::open(const std::string& inFileName)
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
		string theLine;
		while (getline(m_File, theLine))
		{
			istringstream theStringStream(theLine);
			TimedLabel<T> theCurTimedChord;
			theStringStream >> theCurTimedChord.onset();
			string theLabelString;
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
void ChordFileSonicAnnotatorCSV<T>::close()
{
	if (m_FileHasChanged)
	{
		ChordFile::close();
		TimedSAChordSequence theSAChords(m_TimedChords.begin(), m_TimedChords.end());
		//TODO: implement writing theSAChords to csv file
	}
}

#endif  // #ifndef ChordFileSonicAnnotatorCSV_cpp
