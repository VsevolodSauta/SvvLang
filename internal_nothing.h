#pragma once

#define IS_NOTHING(a) (SvvInternalObject_Compare(LINK_AS_OBJECT(a), SvvInternalNothing) != 0)
