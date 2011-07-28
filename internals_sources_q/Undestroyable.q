<Undestroyable> placeHolder

Undestroyable Destroy
	return self

Undestroyable Clone
	return self

Undestroyable DeepClone
	return self

Undestroyable Compare <Undestroyable> undestroyable
	C return (_self < _undestroyable) ? _less : ((_self > _undestroyable) ? _greater : _equal);
