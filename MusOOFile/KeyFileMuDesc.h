#ifndef KeyFileMuDesc_h
#define KeyFileMuDesc_h

//============================================================================
/**
 Class representing a file on disk containing key segments.
 
 @author		Johan Pauwels
 @date			20130416
 */
//============================================================================
#include <string>
#include "MusOOFile/KeyFile.h"
#include "tinyxml2/tinyxml2.h"

namespace MusOO
{
template <typename KeyLabel>
class KeyFileMuDesc : public KeyFile
{
public:
	
	KeyFileMuDesc(const bool inPitchSpelled);
	KeyFileMuDesc(std::string inFileName, const bool inPitchSpelled);
	/** Destructor. */
	virtual ~KeyFileMuDesc();
	
	virtual void open(const std::string& inFileName);
	virtual void close();
	
private:
	
	typedef TimedLabel<KeyLabel> TimedMDKey;
	typedef std::vector<TimedKey> TimedMDKeySequence;
	
	std::string m_FileName;
};
}

template <typename T>
MusOO::KeyFileMuDesc<T>::KeyFileMuDesc(const bool inPitchSpelled)
: KeyFile(inPitchSpelled)
{
}

template <typename T>
MusOO::KeyFileMuDesc<T>::KeyFileMuDesc(std::string inFileName, const bool inPitchSpelled)
: KeyFile(inPitchSpelled)
{
	open(inFileName);
}

template <typename T>
MusOO::KeyFileMuDesc<T>::~KeyFileMuDesc()
{
	close();
}

template <typename T>
void MusOO::KeyFileMuDesc<T>::open(const std::string& inFileName)
{
	m_TimedKeys.clear();
	m_FileHasChanged = false;
	m_FileName = inFileName;
	tinyxml2::XMLDocument theXMLFile;
	theXMLFile.LoadFile(inFileName.c_str());
	tinyxml2::XMLElement* theXMLRoot = theXMLFile.RootElement();
    
	if (theXMLRoot)
	{
		tinyxml2::XMLConstHandle theSegmentHandle(theXMLRoot->FirstChildElement("segment"));
		while (theSegmentHandle.ToElement())
		{
			TimedLabel<T> theCurTimedKey;
			theSegmentHandle.ToElement()->QueryDoubleAttribute("time", &theCurTimedKey.onset());
			theSegmentHandle.ToElement()->QueryDoubleAttribute("length", &theCurTimedKey.offset());
			theCurTimedKey.offset() += theCurTimedKey.onset();
			std::string theLabelString = theSegmentHandle.FirstChildElement("keytype").ToElement()->Attribute("value");
			theCurTimedKey.label() = T(theLabelString);
			m_TimedKeys.push_back(theCurTimedKey);
			theSegmentHandle = theSegmentHandle.NextSiblingElement();
		}
	}
    KeyFile::open(inFileName);
}

template <typename T>
void MusOO::KeyFileMuDesc<T>::close()
{
	if (m_FileHasChanged)
	{
		//TODO: implement writing TimedMDKeySequence to MusicDescription XML file
		tinyxml2::XMLDocument theXMLFile;
		theXMLFile.NewDeclaration("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
		tinyxml2::XMLElement* theXMLRoot = theXMLFile.NewElement("musicdescription");
		theXMLRoot->SetAttribute("xmlns", "http://www.quaero.org/Music_6/1.0");
		theXMLRoot->SetAttribute("xmlns:ns1", "http://www.w3.org/2001/XMLSchema-instance");
		theXMLRoot->SetAttribute("format", "20090701A");
		theXMLRoot->SetAttribute("ns1:schemaLocation", "http://www.quaero.org/Music_6/1.0 http://recherche.ircam.fr/anasyn/quaero/quaero_ctc_6_music.xsd");
		for (TimedKeySequence::const_iterator theKeyIt = m_TimedKeys.begin(); theKeyIt != m_TimedKeys.end(); ++theKeyIt)
		{
			tinyxml2::XMLElement* theCurSegment = theXMLFile.NewElement("segment");
			theXMLRoot->InsertEndChild(theCurSegment);
			theCurSegment->SetAttribute("time", theKeyIt->onset());
			theCurSegment->SetAttribute("length", theKeyIt->offset() - theKeyIt->onset());
			theCurSegment->SetAttribute("sourcetrack", 0);
			tinyxml2::XMLElement* theCurKeyType = theXMLFile.NewElement("keytype");
			theCurSegment->InsertEndChild(theCurKeyType);
			theCurKeyType->SetAttribute("value", T(theKeyIt->label()).str().c_str());
			theCurKeyType->SetAttribute("id", 1);
		}
		theXMLFile.SaveFile(m_FileName.c_str());
	}
}

#endif	// #ifndef KeyFileMuDesc_h
