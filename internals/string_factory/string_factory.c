#include "internals/string_factory/interface.h"
#include "internals/string/interface.h"

SvvInternalAction(SvvInternalStringFactory, GetFromASCIIString, SvvInternalString, char* AsciiString)
{
	SvvInternalString to_return = SvvInternalString_Create();
	int i = 0;
	
	while(AsciiString[i] != 0)
	{
		SvvInternalString_CharAppend(to_return,
			SvvInternalCharFactory_CharGetFromCode(SvvDefaultCharFactory, AsciiString[i]));
	};
	
	return to_return;
};

SvvInternalStringFactory SvvDefaultStringFactory;