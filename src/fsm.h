/*
 * @Author  : Simon Fojtu
 * @Date    : 22.06.2011
 * From     : http://www.netrino.com/Embedded-Systems/How-To/State-Machines-Event-Driven-Systems
 */

#ifndef __FSM_H_
#define __FSM_H_

typedef short Signal;
typedef struct Event Event;
typedef struct Fsm Fsm;
typedef void (*State)(Fsm *, Event const *);

/* Event base class */
struct Event {
	Signal sig;
};

/* Finite State Machine base class */
struct Fsm {
	State state__; /* the current state */
};

/* "inlined" methods of Fsm class */
#define FsmCtor_(me_, init_) ((me_)->state__ = (State)(init_))
#define FsmInit(me_, e_)     (*(me_)->state__)((me_), (e_))
#define FsmDispatch(me_, e_) (*(me_)->state__)((me_), (e_))
#define FsmTran_(me_, targ_) ((me_)->state__ = (State)(targ_))

#endif

