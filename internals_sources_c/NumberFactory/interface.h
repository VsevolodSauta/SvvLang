#pragma once

#include "internals/Object/interface.h"

Object NumberFactory_Create();

Object NumberFactory_FromLong(Object _self, long arg);
Object NumberFactory_FromString(Object _self, Object _string);
Object NumberFactory_FromHexString(Object _self, Object _string);
