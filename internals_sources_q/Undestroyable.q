<Undestroyable> placeHolder

Undestroyable Destroy
	return self

Undestroyable Clone
	return self

Undestroyable DeepClone
	return self

Undestroyable Compare <Undestroyable> undestroyable
	C if(_self < _undestroyable) 
		return less
	C if(_self > _undestroyable)
		return greater
	return equal

