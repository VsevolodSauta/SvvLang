#pragma once

#define SvvInternalAction(Object, Name, Parameters...) SvvInternalObject Object ##_ ##Name (SvvInternalObject Receiver, ##Parameters)
#define SvvInternalCreator(Object) SvvInternalObject Object ##_Create()
#define SvvInternalRoutine(Object, Name, Result, Parameters...) static inline Result Object ##_ ##Name (Object Receiver, ##Parameters)
#define SvvAction(Object, Name) void Object _ ##Name (SvvExternalObject Receiver, SvvMessage Message)

#define SvvInternalDefaultCreator(Object) \
SvvInternalCreator(Object) \
{ \
	SvvInternalObject toReturn = SvvInternalObject_Create(); \
	toReturn->gid = Object ##_GID; \
	SET_ENTITY(toReturn, SvvInternalAllocator_New(Allocator, sizeof(struct Object))); \
	return Object ##_Init(toReturn); \
}
