// see message.xlsx for more explanations

#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <array>

#include "clockint.h"
#include "card.h"

using namespace std;

enum MsgType {
    m_empty,
    m_start,
    m_end,
    m_disptext,
    m_dispeffect,
    m_dispscore,
    m_deal,
    m_bid,
    m_changestake,
    m_setlandlord,
    m_playout,
    m_deny
};

class Message {
    MsgType type;
    bool isr;
    string spar;
    string scard;
    string ext;
public:
    Message(MsgType t = m_empty, bool b = false); // returns a message with unspecified parameters
    Message(const string &s); // decodes s to a message
    MsgType GetType() const; // returns the type
    bool IsRequest() const; // returns whether the message requires a reply
    int GetPar(int k = 0) const; // returns the kth parameter, with k in [0, 8)
    int GetPlayer() const; // returns the 7th parameter, which is usually a player index
    int GetTime() const; // returns the 6th parameter, which is usually a time
    CardSet GetCards() const; // returns the card set parameter
    string GetExtension() const; // returns the extension, usually storing variable-length parameters e.g. text to display
    const string &GetExtensionR() const; // returns the extension by reference
    void SetType(MsgType t); // sets the type to t
    void SetIsRequest(bool b);
    void SetPar(int k, int v); // sets the kth parameter to val
    void SetPlayer(int p);
    void SetTime(int t);
    void SetCards(const CardSet &s);
    void SetExtension(const string &s);
    string String() const; // encodes the message to a string
};

template <int np> class MsgSeries: public array<Message, np> {
public:
    MsgSeries(const Message &m = Message()); // returns a message series duplicating m
    void SetPar(int k, array<int, np> a); // a[i] for the ith message
    void SetPar(int k, ci<np> v); // v goes in the opposite direction from the message index
    void SetPars(int k, array<int, np> a); // sets the first np parameters from k with left rotation
    void SetPlayer(ci<np> v);
    void SetCards(const array<CardSet, np> &a);
};

#endif
