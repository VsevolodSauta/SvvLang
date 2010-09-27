#include "internals/basics.h"

Object true;
Object false;

Object Logic_Not(Object receiver)
{
	return (receiver == true ? false : true);
}