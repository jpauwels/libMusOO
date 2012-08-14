//============================================================================
/**
	Implementation file for SonicAnnotatorCSVChordFile.h
	
	@author		Johan Pauwels
	@date		20110608
*/
//============================================================================

// Guard against multiple template implementation inclusions
#ifndef SonicAnnotatorCSVChordFile_cpp
#define SonicAnnotatorCSVChordFile_cpp

// Includes
#include <sstream>
#include "SonicAnnotatorCSVChordFile.h"

using std::string;
using std::istringstream;

template <typename T>
SonicAnnotatorCSVChordFile<T>::SonicAnnotatorCSVChordFile()
{
}

template <typename T>
SonicAnnotatorCSVChordFile<T>::SonicAnnotatorCSVChordFile(std::string inFileName)
{
	open(inFileName);
}

template <typename T>
SonicAnnotatorCSVChordFile<T>::~SonicAnnotatorCSVChordFile()
{
	close();
}

template <typename T>
void SonicAnnotatorCSVChordFile<T>::open(const std::string& inFileName)
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
}

template <typename T>
void SonicAnnotatorCSVChordFile<T>::close()
{
	if (m_FileHasChanged)
	{
		ChordFile::close();
		SAChordSequence theSAChords(m_TimedChords.begin(), m_TimedChords.end());
		//TODO: implement writing theSAChords to csv file
	}
}

#endif  // #ifndef SonicAnnotatorCSVChordFile_cpp
