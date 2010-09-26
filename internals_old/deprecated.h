#pragma once

#define INT_AS_OBJECT(a) NumberFactory_FromLong(numberFactory, (a))
#define OBJECT_AS_INT(a) Number_GetLong(a)

#define INIT() \
	less = Object_Create(); \
	greater = Object_Create(); \
	equal = Object_Create(); \
	true = Object_Create(); \
	false = Object_Create(); \
	autoreleasePoolsStack = AutoreleasePoolsStack_Create();
