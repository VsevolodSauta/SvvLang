typedef struct Synonim {
	Object _object;
	Object _references;
} *Synonim;

Object Synonim_Create(void);
Object Synonim_Init(Object _self);
Object Synonim_SetObject(Object _self, Object _object);
Object Synonim_Unite(Object _self, Object _synonim);
Object Synonim_AddReference(Object _self, Object _location);
Object Synonim_RemoveReference(Object _self, Object _location);
Object Synonim_RemoveNamespace(Object _self, Object _namespace);
Object Synonim_Destroy(Object _self);
Object Synonim_Clone(Object _self);
Object Synonim_Compare(Object _self, Object _synonim);
