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
class Chroma;
class Mode;

class SimpleInterval
{
public:

	static const SimpleInterval& silence();
	static const SimpleInterval& none();
	static const SimpleInterval& undefined();
	static SimpleInterval unison(); //1
	static SimpleInterval minorSecond(); //b2
    static SimpleInterval majorSecond(); //2
    static SimpleInterval augmentedSecond(); //#2
	static SimpleInterval minorThird(); //b3
    static SimpleInterval majorThird(); //3
    static SimpleInterval diminishedFourth(); //b4
	static SimpleInterval perfectFourth(); //4
	static SimpleInterval augmentedFourth(); //#4
	static SimpleInterval diminishedFifth(); //b5
	static SimpleInterval perfectFifth(); //5
	static SimpleInterval augmentedFifth(); //#5
	static SimpleInterval minorSixth(); //b6
	static SimpleInterval majorSixth(); //6
	static SimpleInterval augmentedSixth(); //#6
	static SimpleInterval diminishedSeventh(); //bb7
	static SimpleInterval minorSeventh(); //b7
	static SimpleInterval majorSeventh(); //7

	friend class Chroma; 
	//to access m_LinePosition in Chroma::operator+=(SimpleInterval), Chroma::operator+=(SimpleInterval) and Chroma::Chroma(Chroma, SimpleInterval)

	/** Default constructor. */
	SimpleInterval();
	SimpleInterval(const Chroma& inRoot, const Chroma& inOther, const bool inUp = true);
	SimpleInterval(const std::string& inMajorDegree, const bool inUp = true);
	SimpleInterval(const std::string& inDegree, const Mode& inMode);
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
	const std::string majorDegree() const;
	const ptrdiff_t diatonicNumber() const;

	const std::string asDegree(const Mode& inMode) const;

	/** Destructor. */
	virtual ~SimpleInterval();
    
	const bool isTrueSimpleInterval() const;
    
	const bool hasSpelling() const;
    SimpleInterval withoutSpelling() const;
    SimpleInterval& ignoreSpelling();

protected:


private:
	//only for creation of static distances
	SimpleInterval(const ptrdiff_t inCircleSteps, const bool inHasSpelling, const size_t inOctaves);
	ptrdiff_t m_LinePosition;
	bool m_HasSpelling;
	static const std::map<size_t,ptrdiff_t> s_MajorDegreeToCircleSteps;
	static const std::map<ptrdiff_t,size_t> s_CircleStepsToMajorDegree;
	static const std::vector<std::string> s_MajorDegrees;
	static const std::vector<std::string> s_MinorDegrees;

};
}
#endif	// #ifndef SimpleInterval_h
