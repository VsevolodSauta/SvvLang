#pragma once

#define SvvInternalAction(Object, Name, Result, Parameters...) Result Object ##_ ##Name (Object Receiver, ##Parameters)
#define SvvInternalCreator(Object) Object Object ##_Create()
#define SvvInternalRoutine(Object, Name, Result, Parameters...) static inline SvvInternalAction(Object, Name, Result, ##Parameters)
#define SvvAction(Object, Name) void Object _ ##Name (SvvExternalObject Receiver, SvvMessage Message)
