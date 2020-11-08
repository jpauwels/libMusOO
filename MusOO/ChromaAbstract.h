#ifndef Chroma_h
#define Chroma_h

//============================================================================
/**
	Class representing a chroma.

	@author		Johan Pauwels
	@date		20100322
*/
//============================================================================
#include "MusOO/SimpleInterval.h"
#include <cstddef>
#include <string>
#include <limits>
#include <vector>
#include <ostream>
#include <stdexcept>

namespace MusOO
{

template <typename Chroma>
class ChromaAbstract
{
public:
    
    template <typename OtherChroma> friend class ChromaAbstract; // to access m_LinePosition and m_HasSpelling from other Chroma types
    
	static const Chroma& silence();
	static const Chroma& none();
	static const Chroma& undefined();
	static Chroma Fb();
	static Chroma Cb();
	static Chroma Gb();
	static Chroma Db();
	static Chroma Ab();
	static Chroma Eb();
	static Chroma Bb();
	static Chroma F();
	static Chroma C();
	static Chroma G();
	static Chroma D();
	static Chroma A();
	static Chroma E();
	static Chroma B();
	static Chroma Fs();
	static Chroma Cs();
	static Chroma Gs();
	static Chroma Ds();
	static Chroma As();
	static Chroma Es();
	static Chroma Bs();

	static const std::vector<Chroma>& circleOfFifths(const Chroma& inStartChroma = ChromaAbstract<Chroma>::A(), const bool inHasSpelling = false);

	/** Default constructor. */
	ChromaAbstract();
    /** Generalised copy constructor. */
    template <typename OtherChroma>
    ChromaAbstract(const ChromaAbstract<OtherChroma>& inChroma);
	ChromaAbstract(const Chroma& inReference, const SimpleInterval& inInterval);

	/** Destructor. */
	virtual ~ChromaAbstract();

	const bool hasSpelling() const;
    Chroma withoutSpelling() const;
    Chroma& ignoreSpelling();

	const bool isTrueChroma() const;

	const bool operator==(const Chroma& inChroma) const;
	const bool operator!=(const Chroma& inChroma) const;
	Chroma& operator+=(const SimpleInterval& inInterval);
	Chroma& operator-=(const SimpleInterval& inInterval);
	const bool operator<(const Chroma& inChroma) const;
	//const Chroma operator+(const SimpleInterval& inInterval) const; as friend function
	//const Chroma operator-(const SimpleInterval& inInterval) const;

    virtual const std::string str() const = 0;
    
	friend class SimpleInterval; //to access stringModifierToCircleSteps() and m_LinePosition in SimpleInterval::SimpleInterval()
    friend class ComplexInterval; //to access m_LinePosition in ComplexInterval::ComplexInterval()

protected:

	static const ptrdiff_t stringModifierToCircleSteps(const std::string& inStringModifier);
    static const ptrdiff_t wrapIntoRange(const ptrdiff_t inValue, const ptrdiff_t inStartIncluded, const ptrdiff_t inEndExcluded);
    static const ptrdiff_t mod(const ptrdiff_t inValue, const ptrdiff_t inModulo);
    static const ptrdiff_t mod12(const ptrdiff_t inValue);

	ptrdiff_t m_LinePosition;
	bool m_HasSpelling;
	
private:
	//only for creation of static chromas
	ChromaAbstract(const ptrdiff_t inCirclePosition, const bool inHasSpelling);

};


template <typename Chroma>
std::ostream& operator<<(std::ostream& inOutputStream, const ChromaAbstract<Chroma>& inChroma)
{
    inOutputStream << inChroma.str();
    return inOutputStream;
}

template <typename Chroma>
std::istream& operator>>(std::istream& inInputStream, ChromaAbstract<Chroma>& inChroma)
{
    std::string theChromaString;
    inInputStream >> theChromaString;
    inChroma = Chroma(theChromaString);
    return inInputStream;
}


template <typename Chroma>
const Chroma& ChromaAbstract<Chroma>::silence()
{
    static const Chroma silence(std::numeric_limits<ptrdiff_t>::max(), true);
    return silence;
}
template <typename Chroma>
const Chroma& ChromaAbstract<Chroma>::none()
{
    static const Chroma noChroma(std::numeric_limits<ptrdiff_t>::max()-1, true);
    return noChroma;
}
template <typename Chroma>
const Chroma& ChromaAbstract<Chroma>::undefined()
{
    static const Chroma undefined(std::numeric_limits<ptrdiff_t>::max()-2, true);
    return undefined;
}
template <typename Chroma>
Chroma ChromaAbstract<Chroma>::Fb()
{
    static const Chroma Fb(-6, true);
    return Fb;
}
template <typename Chroma>
Chroma ChromaAbstract<Chroma>::Cb()
{
    static const Chroma Cb(-5, true);
    return Cb;
}
template <typename Chroma>
Chroma ChromaAbstract<Chroma>::Gb()
{
    static const Chroma Gb(-4, true);
    return Gb;
}
template <typename Chroma>
Chroma ChromaAbstract<Chroma>::Db()
{
    static const Chroma Db(-3, true);
    return Db;
}
template <typename Chroma>
Chroma ChromaAbstract<Chroma>::Ab()
{
    static const Chroma Ab(-2, true);
    return Ab;
}
template <typename Chroma>
Chroma ChromaAbstract<Chroma>::Eb()
{
    static const Chroma Eb(-1, true);
    return Eb;
}
template <typename Chroma>
Chroma ChromaAbstract<Chroma>::Bb()
{
    static const Chroma Bb(0, true);
    return Bb;
}
template <typename Chroma>
Chroma ChromaAbstract<Chroma>::F()
{
    static const Chroma F(1, true);
    return F;
}
template <typename Chroma>
Chroma ChromaAbstract<Chroma>::C()
{
    static const Chroma C(2, true);
    return C;
}
template <typename Chroma>
Chroma ChromaAbstract<Chroma>::G()
{
    static const Chroma G(3, true);
    return G;
}
template <typename Chroma>
Chroma ChromaAbstract<Chroma>::D()
{
    static const Chroma D(4, true);
    return D;
}
template <typename Chroma>
Chroma ChromaAbstract<Chroma>::A()
{
    static const Chroma A(5, true);
    return A;
}
template <typename Chroma>
Chroma ChromaAbstract<Chroma>::E()
{
    static const Chroma E(6, true);
    return E;
}
template <typename Chroma>
Chroma ChromaAbstract<Chroma>::B()
{
    static const Chroma B(7, true);
    return B;
}
template <typename Chroma>
Chroma ChromaAbstract<Chroma>::Fs()
{
    static const Chroma Fs(8, true);
    return Fs;
}
template <typename Chroma>
Chroma ChromaAbstract<Chroma>::Cs()
{
    static const Chroma Cs(9, true);
    return Cs;
}
template <typename Chroma>
Chroma ChromaAbstract<Chroma>::Gs()
{
    static const Chroma Gs(10, true);
    return Gs;
}
template <typename Chroma>
Chroma ChromaAbstract<Chroma>::Ds()
{
    static const Chroma Ds(11, true);
    return Ds;
}
template <typename Chroma>
Chroma ChromaAbstract<Chroma>::As()
{
    static const Chroma As(12, true);
    return As;
}
template <typename Chroma>
Chroma ChromaAbstract<Chroma>::Es()
{
    static const Chroma Es(13, true);
    return Es;
}
template <typename Chroma>
Chroma ChromaAbstract<Chroma>::Bs()
{
    static const Chroma Bs(14, true);
    return Bs;
}
template <typename Chroma>
const std::vector<Chroma>& ChromaAbstract<Chroma>::circleOfFifths(const Chroma& inStartChroma /* = ChromaAbstract<Chroma>::A*/, const bool inHasSpelling /*= false*/)
{
    static std::vector<Chroma> theCircleOfFifths(12);
    for(ptrdiff_t i = 0; i < 12; ++i)
    {
        theCircleOfFifths[i] = Chroma((inStartChroma.m_LinePosition+i)%12, inHasSpelling);
    }
    return theCircleOfFifths;
}

template <typename Chroma>
ChromaAbstract<Chroma>::ChromaAbstract()
: m_LinePosition(Chroma::undefined().m_LinePosition), m_HasSpelling(true)
{
}

template <typename Chroma>
template <typename OtherChroma>
ChromaAbstract<Chroma>::ChromaAbstract(const ChromaAbstract<OtherChroma>& inChroma)
: m_LinePosition(inChroma.m_LinePosition), m_HasSpelling(inChroma.m_HasSpelling)
{
}

template <typename Chroma>
ChromaAbstract<Chroma>::ChromaAbstract(const ptrdiff_t inCirclePosition, const bool inHasSpelling)
: m_LinePosition(inCirclePosition), m_HasSpelling(inHasSpelling)
{
}

template <typename Chroma>
ChromaAbstract<Chroma>::ChromaAbstract(const Chroma& inReference, const SimpleInterval& inInterval)
: m_LinePosition(inReference.m_LinePosition + inInterval.m_LinePosition),
  m_HasSpelling(inReference.m_HasSpelling && inInterval.hasSpelling())
{
    if (!inInterval.isTrueSimpleInterval())
    {
        m_LinePosition = inInterval.m_LinePosition;
        m_HasSpelling = true;
    }
    if (!m_HasSpelling)
    {
        m_LinePosition = wrapIntoRange(m_LinePosition, -1, 11);
    }
}

template <typename Chroma>
ChromaAbstract<Chroma>::~ChromaAbstract()
{
}

template <typename Chroma>
const ptrdiff_t ChromaAbstract<Chroma>::stringModifierToCircleSteps(const std::string& inStringModifier)
{
    ptrdiff_t theCircleModifier = 0;
    for (size_t i = 0; i < inStringModifier.length(); i++)
    {
        //if the next character is a flat, move 7 positions to the left
        if (!inStringModifier.substr(i,1).compare("b"))
        {
            theCircleModifier -= 7;
        }
        //if the next character is a sharp or an "s", move 7 positions to the right
        else if (!inStringModifier.substr(i,1).compare("#") || !inStringModifier.substr(i,1).compare("s"))
        {
            theCircleModifier += 7;
        }
        else
        {
            throw std::invalid_argument("Unknown modifier '" + inStringModifier.substr(i,1) + "'");
        }
    }
    return theCircleModifier;
}

template <typename Chroma>
const bool ChromaAbstract<Chroma>::hasSpelling() const
{
    return m_HasSpelling;
}

template <typename Chroma>
Chroma ChromaAbstract<Chroma>::withoutSpelling() const
{
    return Chroma(static_cast<const Chroma&>(*this)).ignoreSpelling();
}

template <typename Chroma>
Chroma& ChromaAbstract<Chroma>::ignoreSpelling()
{
    if (isTrueChroma())
    {
        m_HasSpelling = false;
    }
    return static_cast<Chroma&>(*this);
}

template <typename Chroma>
const bool ChromaAbstract<Chroma>::operator==(const Chroma& inChroma) const
{
    if (!isTrueChroma() || !inChroma.isTrueChroma() || (m_HasSpelling && inChroma.m_HasSpelling))
    {
        return m_LinePosition == inChroma.m_LinePosition;
    }
    else
    {
        return ((m_LinePosition % 12) + 12) % 12 == ((inChroma.m_LinePosition % 12) + 12) % 12;
    }
}

template <typename Chroma>
const bool ChromaAbstract<Chroma>::operator!=(const Chroma& inChroma) const
{
    return !(*this == inChroma);
}

template <typename Chroma>
Chroma& ChromaAbstract<Chroma>::operator+=(const SimpleInterval& inInterval)
{
    m_LinePosition += inInterval.m_LinePosition;
    m_HasSpelling = m_HasSpelling && inInterval.m_LinePosition;
    return static_cast<Chroma&>(*this);
}

template <typename Chroma>
Chroma& ChromaAbstract<Chroma>::operator-=(const SimpleInterval& inInterval)
{
    m_LinePosition += inInterval.m_LinePosition;
    m_HasSpelling = m_HasSpelling && inInterval.m_LinePosition;
    return static_cast<Chroma&>(*this);
}

template <typename Chroma>
const bool ChromaAbstract<Chroma>::operator<(const Chroma& inChroma) const
{
    if (!isTrueChroma() || !inChroma.isTrueChroma())
    {
        return m_LinePosition < inChroma.m_LinePosition;
    }
    else
    {
        if (((m_LinePosition % 12) + 12) % 12 != ((inChroma.m_LinePosition % 12) + 12) % 12)
        {
            return ((m_LinePosition % 12) + 12) % 12 < ((inChroma.m_LinePosition % 12) + 12) % 12;
        }
        else
        {
            if (m_HasSpelling && inChroma.m_HasSpelling)
            {
                return m_LinePosition < inChroma.m_LinePosition;
            }
            else
            {
                return false;
            }
        }
    }
}

template <typename Chroma>
const bool ChromaAbstract<Chroma>::isTrueChroma() const
{
    return m_LinePosition < std::numeric_limits<ptrdiff_t>::max()-2;
}

template <typename Chroma>
const ptrdiff_t ChromaAbstract<Chroma>::wrapIntoRange(const ptrdiff_t inValue, const ptrdiff_t inStartIncluded, const ptrdiff_t inEndExcluded)
{
    return inStartIncluded + mod(inValue - inStartIncluded, inEndExcluded - inStartIncluded);
}

template <typename Chroma>
const ptrdiff_t ChromaAbstract<Chroma>::mod(const ptrdiff_t inValue, const ptrdiff_t inModulo)
{
    const ptrdiff_t rem = inValue % inModulo;
    return (rem < 0)?inModulo+rem:rem;
}

template <typename Chroma>
const ptrdiff_t ChromaAbstract<Chroma>::mod12(const ptrdiff_t inValue)
{
    return mod(inValue, 12);
}

}
#endif	// #ifndef Chroma_h
