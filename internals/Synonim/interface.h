typedef struct Synonim {
	Object _uid;
	Object _references;
} *Synonim;

Object Synonim_Create(void);
Object Synonim_Init(Object _self);
Object Synonim_SetUID(Object _self, Object _uid);
Object Synonim_GetUID(Object _self);
Object Synonim_Unite(Object _self, Object _synonim);
Object Synonim_AddToNamespaceWithName(Object _self, Object _namespace, Object _name);
Object Synonim_AddReference(Object _self, Object _location);
Object Synonim_RemoveReference(Object _self, Object _location);
Object Synonim_RemoveNamespace(Object _self, Object _namespace);
Object Synonim_Destroy(Object _self);
Object Synonim_Clone(Object _self);
Object Synonim_DeepClone(Object _self);
Object Synonim_Compare(Object _self, Object _synonim);
