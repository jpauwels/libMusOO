#ifndef Mode_h
#define Mode_h

//============================================================================
/**
	Class representing a key mode.

	@author		Johan Pauwels
	@date		20100401
*/
//============================================================================
#include "MusOO/Set.h"
#include "MusOO/SimpleInterval.h"
#include "MusOO/RelativeChordAbstract.h"
#include <cstdlib>
#include <sstream>
#include <algorithm>

namespace MusOO
{
template <typename Mode>
class ModeAbstract : public Set<SimpleInterval, Mode>
{
public:
    
    friend class Key; // to access m_set in Key::chromas()
    template <typename OtherMode> friend class ModeAbstract; // to access m_set from other Mode types
    
	static Mode none();
	static Mode major();
	static Mode minorNatural();
	static Mode minorHarmonic();
	static Mode minorMelodic();
	static Mode minorGeneral();
	static Mode dorian();
	static Mode phrygian();
	static Mode lydian();
	static Mode mixolydian();
	static Mode aeolian();
	static Mode locrian();
	static Mode modal();
    
	/** Default constructor. */
	ModeAbstract();
    /** Generalised copy constructor. */
    template <typename OtherMode>
	ModeAbstract(const ModeAbstract<OtherMode>& inMode);
    
    /** Destructor. */
    virtual ~ModeAbstract();

	size_t diatonicCircleDistance(const SimpleInterval& inInterval1, const SimpleInterval& inInterval2) const;

	/** Returns the diatonic relative triad of a given degree in this mode 
	@param	inDegree			the degree on which a diatonic chord needs to be constructed 
	@return		a relative triad diatonic in this mode built on a given degree */
    template <typename RelativeChord, typename ChordType>
    RelativeChordAbstract<RelativeChord, ChordType> diatonicTriad(size_t inDegree) const;

	const size_t chromaticCOFDistance(SimpleInterval inRootInterval, const Mode& inMode) const;
    
    Mode& addInterval(const SimpleInterval& inInterval);
    Mode& deleteInterval(const SimpleInterval& inInterval);
    Mode& replaceInterval(const SimpleInterval& inIntervalToReplace, const SimpleInterval& inReplacementInterval);
    
    const bool isMajor() const;
    const bool isMinor() const;
    
    virtual const std::string str() const = 0;
    
protected:
    
    using Set<SimpleInterval, Mode>::m_set;
	/* Returns position on diatonic circle of fifths where 0 equals IV, 1 is I, 2 is V and so on */
	ptrdiff_t diatonicPosition(const ptrdiff_t inDiatonicNumber) const;

private:

	// only used for construction of static modes
	ModeAbstract(const SimpleInterval* inIntervalList, const int inNumOfIntervals);
};


template <typename Mode>
std::ostream& operator<<(std::ostream& inOutputStream, const ModeAbstract<Mode>& inMode)
{
    inOutputStream << inMode.str();
    return inOutputStream;
}

template <typename Mode>
std::istream& operator>>(std::istream& inInputStream, ModeAbstract<Mode>& inMode)
{
    std::string theModeString;
    inInputStream >> theModeString;
    inMode = Mode(theModeString);
    return inInputStream;
}


template <typename Mode>
Mode ModeAbstract<Mode>::none()
{
    static const Mode none;
    return none;
}

template <typename Mode>
Mode ModeAbstract<Mode>::major()
{
    const SimpleInterval majorList[] = {SimpleInterval::unison(), SimpleInterval::majorSecond(), SimpleInterval::majorThird(),
        SimpleInterval::perfectFourth(), SimpleInterval::perfectFifth(), SimpleInterval::majorSixth(), SimpleInterval::majorSeventh()};
    static const Mode major(majorList,7);
    return major;
}

template <typename Mode>
Mode ModeAbstract<Mode>::minorNatural()
{
    const SimpleInterval minorNaturalList[] = {SimpleInterval::unison(), SimpleInterval::majorSecond(), SimpleInterval::minorThird(),
        SimpleInterval::perfectFourth(), SimpleInterval::perfectFifth(), SimpleInterval::minorSixth(), SimpleInterval::minorSeventh()};
    static const Mode minorNatural(minorNaturalList,7);
    return minorNatural;
}

template <typename Mode>
Mode ModeAbstract<Mode>::minorHarmonic()
{
    const SimpleInterval minorHarmonicList[] = {SimpleInterval::unison(), SimpleInterval::majorSecond(), SimpleInterval::minorThird(),
        SimpleInterval::perfectFourth(), SimpleInterval::perfectFifth(), SimpleInterval::minorSixth(), SimpleInterval::majorSeventh()};
    static const Mode minorHarmonic(minorHarmonicList,7);
    return minorHarmonic;
}

template <typename Mode>
Mode ModeAbstract<Mode>::minorMelodic()
{
    const SimpleInterval minorMelodicList[] = {SimpleInterval::unison(), SimpleInterval::majorSecond(), SimpleInterval::minorThird(),
        SimpleInterval::perfectFourth(), SimpleInterval::perfectFifth(), SimpleInterval::majorSixth(), SimpleInterval::majorSeventh()};
    static const Mode minorMelodic(minorMelodicList,7);
    return minorMelodic;
}

template <typename Mode>
Mode ModeAbstract<Mode>::minorGeneral()
{
    const SimpleInterval minorGeneralList[] = {SimpleInterval::unison(), SimpleInterval::majorSecond(), SimpleInterval::minorThird(),
        SimpleInterval::perfectFourth(), SimpleInterval::perfectFifth(), SimpleInterval::minorSixth(), SimpleInterval::majorSixth(),
        SimpleInterval::minorSeventh(), SimpleInterval::majorSeventh()};
    static const Mode minorGeneral(minorGeneralList,9);
    return minorGeneral;
}

template <typename Mode>
Mode ModeAbstract<Mode>::dorian()
{
    const SimpleInterval dorianList[] = {SimpleInterval::unison(), SimpleInterval::majorSecond(), SimpleInterval::minorThird(),
        SimpleInterval::perfectFourth(), SimpleInterval::perfectFifth(), SimpleInterval::majorSixth(), SimpleInterval::minorSeventh()};
    static const Mode dorian(dorianList,7);
    return dorian;
}

template <typename Mode>
Mode ModeAbstract<Mode>::phrygian()
{
    const SimpleInterval phrygianList[] = {SimpleInterval::unison(), SimpleInterval::minorSecond(), SimpleInterval::minorThird(),
        SimpleInterval::perfectFourth(), SimpleInterval::perfectFifth(), SimpleInterval::minorSixth(), SimpleInterval::minorSeventh()};
    static const Mode phrygian(phrygianList,7);
    return phrygian;
}

template <typename Mode>
Mode ModeAbstract<Mode>::lydian()
{
    const SimpleInterval lydianList[] = {SimpleInterval::unison(), SimpleInterval::majorSecond(), SimpleInterval::majorThird(),
        SimpleInterval::augmentedFourth(), SimpleInterval::perfectFifth(), SimpleInterval::majorSixth(), SimpleInterval::majorSeventh()};
    static const Mode lydian(lydianList,7);
    return lydian;
}

template <typename Mode>
Mode ModeAbstract<Mode>::mixolydian()
{
    const SimpleInterval mixolydianList[] = {SimpleInterval::unison(), SimpleInterval::majorSecond(), SimpleInterval::majorThird(),
        SimpleInterval::perfectFourth(), SimpleInterval::perfectFifth(), SimpleInterval::majorSixth(), SimpleInterval::minorSeventh()};
    static const Mode mixolydian(mixolydianList,7);
    return mixolydian;
}

template <typename Mode>
Mode ModeAbstract<Mode>::aeolian()
{
    const SimpleInterval aeolianList[] = {SimpleInterval::unison(), SimpleInterval::majorSecond(), SimpleInterval::minorThird(),
        SimpleInterval::perfectFourth(), SimpleInterval::perfectFifth(), SimpleInterval::minorSixth(), SimpleInterval::minorSeventh()};
    static const Mode aeolian(aeolianList,7);
    return aeolian;
}

template <typename Mode>
Mode ModeAbstract<Mode>::locrian()
{
    const SimpleInterval locrianList[] = {SimpleInterval::unison(), SimpleInterval::minorSecond(), SimpleInterval::minorThird(),
        SimpleInterval::perfectFourth(), SimpleInterval::diminishedFifth(), SimpleInterval::minorSixth(), SimpleInterval::minorSeventh()};
    static const Mode locrian(locrianList,7);
    return locrian;
}

template <typename Mode>
Mode ModeAbstract<Mode>::modal()
{
    const SimpleInterval modalList[] = {SimpleInterval::unison()};
    static const Mode modal(modalList,1);
    return modal;
}

template <typename Mode>
ModeAbstract<Mode>::ModeAbstract()
: Set<SimpleInterval, Mode>()
{
}

template <typename Mode>
template <typename OtherMode>
ModeAbstract<Mode>::ModeAbstract(const ModeAbstract<OtherMode>& inMode)
: Set<SimpleInterval, Mode>(inMode)
{
}

template <typename Mode>
ModeAbstract<Mode>::ModeAbstract(const SimpleInterval* inIntervalList, const int inNumOfIntervals)
: Set<SimpleInterval, Mode>(inIntervalList, inNumOfIntervals)
{
}

template <typename Mode>
ModeAbstract<Mode>::~ModeAbstract()
{
}

template <typename Mode>
size_t ModeAbstract<Mode>::diatonicCircleDistance(const SimpleInterval& inInterval1, const SimpleInterval& inInterval2) const
{
    if ((m_set.count(inInterval1) == 0 || m_set.count(inInterval2) == 0) &&
        m_set.count(inInterval1) != m_set.count(inInterval2))
    {
        return m_set.size()/2;
    }
    ptrdiff_t theDiatonicPosition1 = diatonicPosition(inInterval1.diatonicNumber());
    ptrdiff_t theDiatonicPosition2 = diatonicPosition(inInterval2.diatonicNumber());
    return std::min(std::abs(theDiatonicPosition1-theDiatonicPosition2), 7 - std::abs(theDiatonicPosition1-theDiatonicPosition2));
}

template <typename Mode>
ptrdiff_t ModeAbstract<Mode>::diatonicPosition(const ptrdiff_t inDiatonicNumber) const
{
    return 2 * (inDiatonicNumber % 4) + inDiatonicNumber / 4;
}

template <typename Mode>
template <typename RelativeChord, typename ChordType>
RelativeChordAbstract<RelativeChord, ChordType> ModeAbstract<Mode>::diatonicTriad(size_t inDegree) const
{
    SimpleInterval theRootInterval = this->getDiatonicInterval(inDegree);
    ChordType theType = ChordType::rootOnly();
    theType = theType.addInterval(this->getDiatonicInterval((inDegree+1)%7+1) - theRootInterval);
    theType = theType.addInterval(this->getDiatonicInterval((inDegree+3)%7+1) - theRootInterval);
    return RelativeChord(theRootInterval, theType);
}

template <typename Mode>
const size_t ModeAbstract<Mode>::chromaticCOFDistance(SimpleInterval inRootInterval, const Mode& inMode) const
{
    if (isMinor())
    {
        inRootInterval -= SimpleInterval::minorThird();
    }
    if (inMode.isMinor())
    {
        inRootInterval += SimpleInterval::minorThird();
    }
    return std::min(inRootInterval.circleStepsCCW(), inRootInterval.circleStepsCW());
}

template <typename Mode>
Mode& ModeAbstract<Mode>::addInterval(const SimpleInterval& inInterval)
{
    return Mode::add(inInterval);
}

template <typename Mode>
Mode& ModeAbstract<Mode>::deleteInterval(const SimpleInterval& inInterval)
{
    return Mode::remove(inInterval);
}

template <typename Mode>
Mode& ModeAbstract<Mode>::replaceInterval(const SimpleInterval& inIntervalToReplace, const SimpleInterval& inReplacementInterval)
{
    return Mode::replace(inIntervalToReplace, inReplacementInterval);
}

template <typename Mode>
const bool ModeAbstract<Mode>::isMajor() const
{
    return this->contains(SimpleInterval::majorThird());
}

template <typename Mode>
const bool ModeAbstract<Mode>::isMinor() const
{
    return this->contains(SimpleInterval::minorThird());
}


}
#endif	// #ifndef Mode_h
