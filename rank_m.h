//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/application/myProject/rank.msg.
//

#ifndef _RANK_M_H_
#define _RANK_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include "ApplicationPacket_m.h"
// }}

/**
 * Struct generated from src/node/application/myProject/rank.msg:7 by nedtool.
 */
struct srank
{
    srank();
    int rank;
};

void doPacking(cCommBuffer *b, srank& a);
void doUnpacking(cCommBuffer *b, srank& a);

/**
 * Class generated from <tt>src/node/application/myProject/rank.msg:11</tt> by nedtool.
 * <pre>
 * packet Rank extends ApplicationPacket
 * {
 *     srank myrank;
 * }
 * </pre>
 */
class Rank : public ::ApplicationPacket
{
  protected:
    srank myrank_var;

  private:
    void copy(const Rank& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Rank&);

  public:
    Rank(const char *name=NULL, int kind=0);
    Rank(const Rank& other);
    virtual ~Rank();
    Rank& operator=(const Rank& other);
    virtual Rank *dup() const {return new Rank(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual srank& getMyrank();
    virtual const srank& getMyrank() const {return const_cast<Rank*>(this)->getMyrank();}
    virtual void setMyrank(const srank& myrank);
};

inline void doPacking(cCommBuffer *b, Rank& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Rank& obj) {obj.parsimUnpack(b);}


#endif // ifndef _RANK_M_H_
