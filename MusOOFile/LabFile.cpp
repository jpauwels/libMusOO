//============================================================================
/**
	Implementation file for LabFile.h

	@author		Johan Pauwels
	@date		20100325
*/
//============================================================================

// Guard against multiple template implementation inclusions
#ifndef LabFile_CPP
#define LabFile_CPP

// Includes
#include <string>
	using std::string;
#include <sstream>
	using std::istringstream;
	using std::stringbuf;
#include <stdexcept>
	using std::runtime_error;
	using std::invalid_argument;
	using std::length_error;
#include <iomanip>
	using std::fixed;
	using std::setprecision;
#include "LabFile.h"

template <typename Label>
LabFile<Label>::LabFile(const std::vector<std::string>& inHeader /*= std::vector<std::string>()*/)
: m_FileHasChanged(false), m_Header(inHeader)
{
	if (!m_Header.empty() && m_Header.size() != 3)
	{
		throw length_error("The header has an invalid number of elements.");
	}
}

template <typename Label>
LabFile<Label>::LabFile(const std::string& inFileName,
						const std::vector<std::string>& inHeader /*= std::vector<std::string>()*/)
: m_Header(inHeader)
{
	open(inFileName);
}

template <typename Label>
LabFile<Label>::~LabFile()
{
	close();
}

template <typename Label>
void LabFile<Label>::open(const std::string& inFileName)
{
	if (m_LabFile.is_open())
	{
		close();
	}
	m_TimedLabels.clear();
	m_FileHasChanged = false;
	m_Iterator = m_TimedLabels.begin();
	m_LabFileName = inFileName;
	m_LabFile.open(inFileName.c_str(), std::fstream::in);
	if (m_LabFile.is_open())
	{
		string theLine;
		if (!m_Header.empty())
		{
			getline(m_LabFile, theLine);
			istringstream theStringStream(theLine);
			string theOnsetCol, theOffsetCol, theLabelCol;
			theStringStream >> theOnsetCol >> theOffsetCol >> theLabelCol;
			if (m_Header[0].compare(theOnsetCol) != 0 || m_Header[1].compare(theOffsetCol) != 0 ||
				m_Header[2].compare(theLabelCol) != 0)
			{
				throw invalid_argument("The file " + inFileName + " has a malformed header.");
			}
		}
		while (getline(m_LabFile, theLine))
		{
			istringstream theStringStream(theLine);
			TimedLabel<Label> theCurLabel;
			theStringStream >> theCurLabel.onset();
			theStringStream >> theCurLabel.offset();
			//get remaining content of stringstream
			theStringStream.clear(); //clear error flags for files without onset/offset
			string theLabelString;
			theStringStream >> theLabelString;
			string theExtraString;
			getline(theStringStream,theExtraString);
			theLabelString += theExtraString;
			// handle windows files under unix
			if (theLabelString[theLabelString.size()-1] == '\r')
			{
				theLabelString.erase(theLabelString.size()-1);
			}
			theCurLabel.label() = Label(theLabelString);
			m_TimedLabels.push_back(theCurLabel);
		}
	}
}

template <typename Label>
const std::vector<TimedLabel<Label> >& LabFile<Label>::readAll()
{
	return m_TimedLabels;
}

template <typename Label>
void LabFile<Label>::writeAll(std::vector<TimedLabel<Label> >& inLabels)
{
	m_TimedLabels = inLabels;
	m_FileHasChanged = true;
}

template <typename Label>
TimedLabel<Label>& LabFile<Label>::readNext()
{
	return *m_Iterator++;
}

template <typename Label>
void LabFile<Label>::add(TimedLabel<Label>& inLabel)
{
	m_TimedLabels.push_back(inLabel);
	m_FileHasChanged = true;
}

template <typename Label>
void LabFile<Label>::close()
{
	if (m_LabFile.is_open())
	{
		m_LabFile.close();
	}
	if (m_FileHasChanged)
	{
		m_LabFile.clear();
		m_LabFile.open(m_LabFileName.c_str(), std::fstream::out);
		if (!m_LabFile.is_open())
		{
			throw runtime_error("Could not open file " + m_LabFileName + " for writing");
		}
		if (!m_Header.empty())
		{
			m_LabFile << m_Header[0] << "\t" << m_Header[1] << "\t" << m_Header[2] << "\n";
		}
		m_LabFile << fixed << setprecision(7);
		for (size_t i = 0; i < m_TimedLabels.size(); ++i)
		{
			m_LabFile << m_TimedLabels[i].onset() << "\t" << m_TimedLabels[i].offset() << "\t"
				<< m_TimedLabels[i].label().str() << "\n";
		}
		m_LabFile.flush();
		m_LabFile.close();
	}
}

#endif  // #ifndef LabFile_CPP
