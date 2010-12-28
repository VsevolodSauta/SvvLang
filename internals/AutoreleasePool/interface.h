typedef struct AutoreleasePool {
	Object _stack;
} *AutoreleasePool;

Object AutoreleasePool_Create(void);
Object AutoreleasePool_Init(Object _self);
Object AutoreleasePool_Dump(Object _self);
Object AutoreleasePool_Depth(Object _self);
Object AutoreleasePool_PushFrame(Object _self);
Object AutoreleasePool_PopFrame(Object _self);
Object AutoreleasePool_Add(Object _self, Object _object);
Object AutoreleasePool_Destroy(Object _self);
Object AutoreleasePool_Compare(Object _self, Object _autoreleasePool);
Object AutoreleasePool_Clone(Object _self);
