#include "internals/basics.h"
#include "internals/Array/interface.h"

Object Array_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct Array));
	toReturn->gid = 14860442650834503680ull;
	Object_SetComparator(toReturn, &Array_Compare);
	Object_SetDestructor(toReturn, &Array_Destroy);
	Object_SetCloner(toReturn, &Array_Clone);
	Object_SetDeepCloner(toReturn, &Array_DeepClone);
	((Array) (toReturn->entity))->size = NumberFactory_NumberFromLong(_numberFactory, 0);
	return toReturn;
}

Object Array_Compare(Object receiver, Object array)
{
	return Object_Compare(Object_Hash(receiver), Object_Hash(array));
}

Object Array_Clone(Object receiver)
{
	Object toReturn = Array_Create();
	Array_SetSize(toReturn, NumberFactory_FromLong(_numberFactory, ((Array) (receiver->entity))->size));
	int i;
	for(i = 0; i < ((Array) (receiver->entity))->size; i++)
	{
		Object_Retain(((Array) (toReturn->entity))->data[i] = ((Array) (receiver->entity))->data[i]);
	}
	return toReturn;
};

Object Array_Destroy(Object receiver)
{
	int i;
	for(i = 0; i < ((Array) (receiver->entity))->size; i++)
	{
		Object_Release(((Array) (receiver->entity))->data[i]);
	}
	return Object_Destroy(receiver);
}

Object Array_SetSize(Object receiver, Object size)
{
	((Array) (receiver->entity))->size = Object_Retain(size);
	((Array) (receiver->entity))->data = Allocator_New(_allocator, sizeof(Object) * Number_GetLong(size));
	return receiver;
}

Object Array_GetAt(Object receiver, Object position)
{
	return ((Array) (receiver->entity))->data[Number_GetLong(position)];
}

Object Array_PutAt(Object receiver, Object object, Object position)
{
	Object_Release(((Array) (receiver->entity))->data[Number_GetLong(position)]);
	((Array) (receiver->entity))->data[Number_GetLong(position)] = Object_Retain(object);
	return receiver;
}
