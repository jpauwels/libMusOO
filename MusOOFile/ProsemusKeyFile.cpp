//============================================================================
/**
	Implementation file for ProsemusKeyFile.h

	@author		Johan Pauwels
	@date		20110111
*/
//============================================================================

// Includes
#include <stdexcept>
#include "ProsemusKeyFile.h"

using std::string;

ProsemusKeyFile::ProsemusKeyFile(const bool inPitchSpelled)
: KeyFile(inPitchSpelled)
{
}

ProsemusKeyFile::ProsemusKeyFile(std::string inFileName, const bool inPitchSpelled)
: KeyFile(inPitchSpelled)
{
	open(inFileName);
}

ProsemusKeyFile::~ProsemusKeyFile()
{
	close();
}

void ProsemusKeyFile::open(const std::string& inFileName)
{
	if (m_File.is_open())
	{
		close();
	}
	this->m_TimedKeys.clear();
	this->m_FileHasChanged = false;
	m_FileName = inFileName;
	m_File.open(inFileName.c_str(), std::fstream::in);
	if (m_File.is_open())
	{
		string theLine;
		getline(m_File, theLine);
		if (!theLine.compare("C"))
		{
			this->m_TimedKeys = KeySequence(1, TimedKey(0., std::numeric_limits<double>::max(),
				Key(Chroma::C(), Mode::major())));
		}
		else if (!theLine.compare("Am"))
		{
			this->m_TimedKeys = KeySequence(1, TimedKey(0., std::numeric_limits<double>::max(),
				Key(Chroma::A(), Mode::minorHarmonic())));
		}
		else
		{
			throw std::runtime_error("Unknown Prosemus key " + theLine);
		}
	}
    KeyFile::open(inFileName);
}

void ProsemusKeyFile::close()
{
	if (m_File.is_open())
	{
		m_File.close();
	}
	if (m_FileHasChanged)
	{
		m_File.clear();
		m_File.open(m_FileName.c_str(), std::fstream::out);
		if (!m_File.is_open())
		{
			throw std::runtime_error("Could not open file " + m_FileName + " for writing");
		}
		if (this->m_TimedKeys == KeySequence(1, TimedKey(0., std::numeric_limits<double>::max(),
			Key(Chroma::C(), Mode::major()))))
		{
			m_File << "C";
		}
		else if (this->m_TimedKeys == KeySequence(1, TimedKey(0., std::numeric_limits<double>::max(),
			Key(Chroma::A(), Mode::minorHarmonic()))))
		{
			m_File << "Am";
		}
		else
		{
			throw std::runtime_error("Key not representable in Prosemus format");
		}
		m_File.flush();
		m_File.close();
	}
}
