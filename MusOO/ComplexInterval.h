#ifndef ComplexInterval_h
#define ComplexInterval_h

//============================================================================
/**
	Class representing a complex musical interval.

	@author		Johan Pauwels
	@date		20100916
*/
//============================================================================
#include "MusOO/SimpleInterval.h"
#include <cstddef>
#include <string>
#include <map>
#include <vector>

namespace MusOO
{

class ComplexInterval
{
public:

	static const ComplexInterval& silence();
	static const ComplexInterval& none();
	static const ComplexInterval& undefined();
	static ComplexInterval unison(); //1
	static ComplexInterval minorSecond(); //b2
	static ComplexInterval majorSecond(); //2
	static ComplexInterval minorThird(); //b3
	static ComplexInterval majorThird(); //3
	static ComplexInterval perfectFourth(); //4
	static ComplexInterval augmentedFourth(); //#4
	static ComplexInterval diminishedFifth(); //b5
	static ComplexInterval perfectFifth(); //5
	static ComplexInterval augmentedFifth(); //#5
	static ComplexInterval minorSixth(); //b6
	static ComplexInterval majorSixth(); //6
	static ComplexInterval augmentedSixth(); //#6
	static ComplexInterval diminishedSeventh(); //bb7
	static ComplexInterval minorSeventh(); //b7
	static ComplexInterval majorSeventh(); //7
	static ComplexInterval octave(); //8
	static ComplexInterval minorNinth(); //b9
	static ComplexInterval majorNinth(); //9
	static ComplexInterval augmentedNinth(); //#9
	static ComplexInterval diminishedEleventh(); //b11
	static ComplexInterval perfectEleventh(); //11
	static ComplexInterval augmentedEleventh(); //#11
	static ComplexInterval minorThirteenth(); //b13
	static ComplexInterval majorThirteenth(); //13

	template <typename Chroma> friend class ChromaAbstract;
	//to access m_LinePosition in Chroma::operator+=(ComplexInterval), Chroma::operator+=(ComplexInterval) and Chroma::Chroma(Chroma, ComplexInterval)

	/** Default constructor. */
	ComplexInterval();
    template <typename Chroma, typename OtherChroma>
	ComplexInterval(const ChromaAbstract<Chroma>& inRoot, const ChromaAbstract<OtherChroma>& inOther, const bool inUp = true);
//	ComplexInterval(const std::string& inMajorDegree); const bool inUp = true);
    template <typename Mode>
	ComplexInterval(const std::string& inDegree, const ModeAbstract<Mode>& inMode);
	ComplexInterval(const ptrdiff_t inSemiTones);
    ComplexInterval(const SimpleInterval& inSimpleInterval, const size_t inOctaves = 0);

	// Operators
	bool operator==(const ComplexInterval& inComplexInterval) const;
	bool operator!=(const ComplexInterval& inComplexInterval) const;
	bool operator<(const ComplexInterval& inComplexInterval) const;
	ComplexInterval& operator+=(const ComplexInterval& inComplexInterval);
	ComplexInterval& operator-=(const ComplexInterval& inComplexInterval);
	const ComplexInterval operator+(const ComplexInterval& inComplexInterval) const;
	const ComplexInterval operator-(const ComplexInterval& inComplexInterval) const;
	//ComplexInterval& operator-(); //inverse in-place
	//const ComplexInterval operator-() const; //inverse out-of-place

	// Observers
	const ptrdiff_t semiTonesUp() const;
	const ptrdiff_t semiTonesDown() const;
	const ptrdiff_t circleStepsCW() const;
	const ptrdiff_t circleStepsCCW() const;
	const std::string majorDegreeString() const;
	const ptrdiff_t diatonicNumber() const;

    template <typename Mode>
	const std::string asDegree(const ModeAbstract<Mode>& inMode) const;

	/** Destructor. */
	virtual ~ComplexInterval();
    
	const bool isTrueInterval() const;
    
	const bool hasSpelling() const;
    ComplexInterval withoutSpelling() const;
    ComplexInterval& ignoreSpelling();
    const SimpleInterval& simpleInterval() const;

protected:


private:
    SimpleInterval m_simpleInterval;
	size_t m_Octaves;

};

template <typename Chroma, typename OtherChroma>
ComplexInterval::ComplexInterval(const ChromaAbstract<Chroma>& inRoot, const ChromaAbstract<OtherChroma>& inOther, const bool inUp /*= true*/)
: m_Octaves(0)
{
    if (!inRoot.isTrueChroma() || !inOther.isTrueChroma())
    {
        *this = undefined();
    }
    else
    {
        ptrdiff_t linePosition;
        if (inUp)
        {
            linePosition = inOther.m_LinePosition - inRoot.m_LinePosition;
        }
        else
        {
            linePosition = inRoot.m_LinePosition - inOther.m_LinePosition;
        }
        m_simpleInterval = SimpleInterval(linePosition, inRoot.hasSpelling() && inOther.hasSpelling());
    }
}

template <typename Mode>
ComplexInterval::ComplexInterval(const std::string& inDegree, const ModeAbstract<Mode>& inMode)
: m_simpleInterval(SimpleInterval(inDegree, inMode)), m_Octaves(0)
{
}

template <typename Mode>
const std::string ComplexInterval::asDegree(const ModeAbstract<Mode>& inMode) const
{
    return m_simpleInterval.asDegree(inMode);
}

}
#endif	// #ifndef ComplexInterval_h
