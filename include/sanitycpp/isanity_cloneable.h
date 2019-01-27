#ifndef ISANITY_CLONEABLE
#define ISANITY_CLONEABLE

class ISanityCloneable {
public:
    virtual ISanityCloneable* clone() const { return new ISanityCloneable(*this); }
};

#endif // ISANITY_CLONEABLE