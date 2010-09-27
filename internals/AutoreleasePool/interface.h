typedef struct AutoreleasePool {
	Object stack;
} *AutoreleasePool;
Object AutoreleasePool_Create(void);
Object AutoreleasePool_Init(Object self);
Object AutoreleasePool_PushFrame(Object self);
Object AutoreleasePool_PopFrame(Object self, Object object);
Object AutoreleasePool_Add(Object self, Object object);
Object AutoreleasePool_Destroy(Object self);
Object AutoreleasePool_Compare(Object self, Object autoreleasePool);
Object AutoreleasePool_Clone(Object self);
