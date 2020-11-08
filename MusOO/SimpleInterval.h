#ifndef SimpleInterval_h
#define SimpleInterval_h

//============================================================================
/**
	Class representing a simple musical interval (< octave).

	@author		Johan Pauwels
	@date		20100916
*/
//============================================================================
#include <cstddef>
#include <string>
#include <map>
#include <vector>

namespace MusOO
{
template <typename Chroma> class ChromaAbstract;
template <typename Mode> class ModeAbstract;

class SimpleInterval
{
public:

	static const SimpleInterval& silence();
	static const SimpleInterval& none();
	static const SimpleInterval& undefined();
	static SimpleInterval unison(); //1
    static SimpleInterval diminishedSecond(); //bb2
	static SimpleInterval minorSecond(); //b2
    static SimpleInterval majorSecond(); //2
    static SimpleInterval augmentedSecond(); //#2
    static SimpleInterval diminishedThird(); //bb3
	static SimpleInterval minorThird(); //b3
    static SimpleInterval majorThird(); //3
    static SimpleInterval augmentedThird(); //#3
    static SimpleInterval diminishedFourth(); //b4
	static SimpleInterval perfectFourth(); //4
	static SimpleInterval augmentedFourth(); //#4
	static SimpleInterval diminishedFifth(); //b5
	static SimpleInterval perfectFifth(); //5
	static SimpleInterval augmentedFifth(); //#5
    static SimpleInterval diminishedSixth(); //bb6
	static SimpleInterval minorSixth(); //b6
	static SimpleInterval majorSixth(); //6
	static SimpleInterval augmentedSixth(); //#6
	static SimpleInterval diminishedSeventh(); //bb7
	static SimpleInterval minorSeventh(); //b7
	static SimpleInterval majorSeventh(); //7
    static SimpleInterval augmentedSeventh(); //#7

	template <typename Chroma> friend class ChromaAbstract; 
	//to access m_LinePosition in Chroma::operator+=(SimpleInterval), Chroma::operator+=(SimpleInterval) and Chroma::Chroma(Chroma, SimpleInterval)
    friend class ComplexInterval; // to access SimpleInterval::SimpleInterval(const ptrdiff_t, const bool) from ComplexInterval::ComplexInterval

	/** Default constructor. */
	SimpleInterval();
    template <typename Chroma, typename OtherChroma>
	SimpleInterval(const ChromaAbstract<Chroma>& inRoot, const ChromaAbstract<OtherChroma>& inOther, const bool inUp = true);
	SimpleInterval(const std::string& inMajorDegree, const bool inUp = true);
    template <typename Mode>
	SimpleInterval(const std::string& inDegree, const ModeAbstract<Mode>& inMode);
	SimpleInterval(const ptrdiff_t inSemiTones);

	// Operators
	bool operator==(const SimpleInterval& inSimpleInterval) const;
	bool operator!=(const SimpleInterval& inSimpleInterval) const;
	bool operator<(const SimpleInterval& inSimpleInterval) const;
	SimpleInterval& operator+=(const SimpleInterval& inSimpleInterval);
	SimpleInterval& operator-=(const SimpleInterval& inSimpleInterval);
	const SimpleInterval operator+(const SimpleInterval& inSimpleInterval) const;
	const SimpleInterval operator-(const SimpleInterval& inSimpleInterval) const;
	//SimpleInterval& operator-(); //inverse in-place
	//const SimpleInterval operator-() const; //inverse out-of-place

	// Observers
	const ptrdiff_t semiTonesUp() const;
	const ptrdiff_t semiTonesDown() const;
	const ptrdiff_t circleStepsCW() const;
	const ptrdiff_t circleStepsCCW() const;
    const std::tuple<ptrdiff_t, ptrdiff_t> majorDegree() const;
	const std::string majorDegreeString() const;
	const ptrdiff_t diatonicNumber() const;

    template <typename Mode>
	const std::string asDegree(const ModeAbstract<Mode>& inMode) const;

	/** Destructor. */
	virtual ~SimpleInterval();
    
	const bool isTrueSimpleInterval() const;
    
	const bool hasSpelling() const;
    SimpleInterval withoutSpelling() const;
    SimpleInterval& ignoreSpelling();

protected:


private:
	//only for creation of static distances
	SimpleInterval(const ptrdiff_t inCircleSteps, const bool inHasSpelling);
	ptrdiff_t m_LinePosition;
	bool m_HasSpelling;
	static const std::map<size_t,ptrdiff_t> s_MajorDegreeToCircleSteps;
	static const std::map<ptrdiff_t,size_t> s_CircleStepsToMajorDegree;
	static const std::vector<std::string> s_MajorDegrees;
	static const std::vector<std::string> s_MinorDegrees;

};

template <typename Chroma, typename OtherChroma>
SimpleInterval::SimpleInterval(const ChromaAbstract<Chroma>& inRoot, const ChromaAbstract<OtherChroma>& inOther, const bool inUp /*= true*/)
{
    if (!inRoot.isTrueChroma() || !inOther.isTrueChroma())
    {
        *this = undefined();
    }
    else
    {
        if (inUp)
        {
            m_LinePosition = inOther.m_LinePosition - inRoot.m_LinePosition;
        }
        else
        {
            m_LinePosition = inRoot.m_LinePosition - inOther.m_LinePosition;
        }
        m_HasSpelling = inRoot.hasSpelling() && inOther.hasSpelling();
        if (!m_HasSpelling)
        {
            m_LinePosition = Chroma::wrapIntoRange(m_LinePosition, -6, 6);
        }
    }
}

template <typename Mode>
SimpleInterval::SimpleInterval(const std::string& inDegree, const ModeAbstract<Mode>& inMode)
{
    ptrdiff_t theSemiTones;
    if (inMode.isMajor())
    {
        theSemiTones = std::find(s_MajorDegrees.begin(), s_MajorDegrees.end(), inDegree) - s_MajorDegrees.begin();
    }
    else
    {
        theSemiTones = std::find(s_MinorDegrees.begin(), s_MinorDegrees.end(), inDegree) - s_MinorDegrees.begin();
    }
    m_LinePosition = ((7*theSemiTones % 12) + 12) % 12;
    m_HasSpelling = false;
}

template <typename Mode>
const std::string SimpleInterval::asDegree(const ModeAbstract<Mode>& inMode) const
{
    if (inMode.isMajor())
    {
        return s_MajorDegrees[((semiTonesUp() % 12) + 12) % 12];
    }
    else
    {
        return s_MinorDegrees[((semiTonesUp() % 12) + 12) % 12];
    }
}

}
#endif	// #ifndef SimpleInterval_h
