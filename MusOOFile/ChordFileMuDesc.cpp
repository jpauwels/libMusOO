//============================================================================
/**
 Implementation file for ChordFileMuDesc.h
 
 @author		Johan Pauwels
 @date			20120614
 */
//============================================================================

// Guard against multiple template implementation inclusions
#ifndef ChordFileMuDesc_cpp
#define ChordFileMuDesc_cpp

// Includes
#include "ChordFileMuDesc.h"
#include "tinyxml2/tinyxml2.h"

using std::string;
using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;
using tinyxml2::XMLConstHandle;

template <typename T>
ChordFileMuDesc<T>::ChordFileMuDesc(const bool inPitchSpelled)
: ChordFile(inPitchSpelled)
{
}

template <typename T>
ChordFileMuDesc<T>::ChordFileMuDesc(std::string inFileName, const bool inPitchSpelled)
: ChordFile(inPitchSpelled)
{
	open(inFileName);
}

template <typename T>
ChordFileMuDesc<T>::~ChordFileMuDesc()
{
	close();
}

template <typename T>
void ChordFileMuDesc<T>::open(const std::string& inFileName)
{	
	m_TimedChords.clear();
	m_FileHasChanged = false;
	m_FileName = inFileName;
	tinyxml2::XMLDocument theXMLFile;
	theXMLFile.LoadFile(inFileName.c_str());
	XMLElement* theXMLRoot = theXMLFile.RootElement();

	if (theXMLRoot)
	{
		XMLConstHandle theSegmentHandle(theXMLRoot->FirstChildElement("segment"));
		while (theSegmentHandle.ToElement())
		{
			TimedLabel<T> theCurTimedChord;
			theSegmentHandle.ToElement()->QueryDoubleAttribute("time", &theCurTimedChord.onset());
			theSegmentHandle.ToElement()->QueryDoubleAttribute("length", &theCurTimedChord.offset());
			theCurTimedChord.offset() += theCurTimedChord.onset();
			string theLabelString = theSegmentHandle.FirstChildElement("chordtype").ToElement()->Attribute("value");
			theCurTimedChord.label() = T(theLabelString);
			m_TimedChords.push_back(theCurTimedChord);
			theSegmentHandle = theSegmentHandle.NextSiblingElement();
		}
	}
    ChordFile::open(inFileName);
}

template <typename T>
void ChordFileMuDesc<T>::close()
{
	if (m_FileHasChanged)
	{
		ChordFile::close();
		//TODO: implement writing TimedMDChordSequence to MusicDescription XML file
		XMLDocument theXMLFile;
		theXMLFile.NewDeclaration("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
		XMLElement* theXMLRoot = theXMLFile.NewElement("musicdescription");
		theXMLRoot->SetAttribute("xmlns", "http://www.quaero.org/Music_6/1.0");
		theXMLRoot->SetAttribute("xmlns:ns1", "http://www.w3.org/2001/XMLSchema-instance");
		theXMLRoot->SetAttribute("format", "20090701A");
		theXMLRoot->SetAttribute("ns1:schemaLocation", "http://www.quaero.org/Music_6/1.0 http://recherche.ircam.fr/anasyn/quaero/quaero_ctc_6_music.xsd");
		for (TimedChordSequence::const_iterator theChordIt = m_TimedChords.begin(); theChordIt != m_TimedChords.end(); ++theChordIt)
		{
			XMLElement* theCurSegment = theXMLFile.NewElement("segment");
			theXMLRoot->InsertEndChild(theCurSegment);
			theCurSegment->SetAttribute("time", theChordIt->onset());
			theCurSegment->SetAttribute("length", theChordIt->offset() - theChordIt->onset());
			theCurSegment->SetAttribute("sourcetrack", 0);
			XMLElement* theCurChordType = theXMLFile.NewElement("chordtype");
			theCurSegment->InsertEndChild(theCurChordType);
			theCurChordType->SetAttribute("value", T(theChordIt->label()).str().c_str());
			theCurChordType->SetAttribute("id", 1);
		}
		theXMLFile.SaveFile(m_FileName.c_str());
	}
}

#endif  // #ifndef ChordFileMuDesc_cpp
