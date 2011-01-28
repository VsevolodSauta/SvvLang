#include "internals/basics.h"
#include "internals/Undestroyable/interface.h"

Object _true;
Object _false;
Object _yes;
Object _no;

Object Logic_Create()
{
	return Undestroyable_Create();
}

Object Logic_Not(Object receiver)
{
	return (receiver == _true ? _false : _true);
}

Object Logic_And(Object receiver, Object arg)
{
	return ((receiver != _false) && (arg != _false) ? _true : _false );
}

Object Logic_Or(Object receiver, Object arg)
{
	return ((receiver != _false) || (arg != _false) ? _true : _false);
}

Object Logic_Xor(Object receiver, Object arg)
{
	return ((receiver != _false) ^ (arg != _false) ? _true : _false);
}

