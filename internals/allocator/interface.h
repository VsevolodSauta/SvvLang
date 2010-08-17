#pragma once
#include "internals/object/interface.h"

void* SvvInternalAllocator_New(SvvInternalObject Receiver, int Size);
void* SvvInternalAllocator_Resize(SvvInternalObject Receiver, void*, int Size);
void SvvInternalAllocator_Delete(SvvInternalObject Receiver, void*);
