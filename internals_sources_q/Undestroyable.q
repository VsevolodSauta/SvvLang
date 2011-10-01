<Undestroyable@Object> placeHolder

Undestroyable Destroy
	return self

Undestroyable CompareSameGID <Undestroyable> undestroyable
	C if(_self < _undestroyable)
		return less
	C if(_self > _undestroyable)
		return greater
	return equal

// Можно не увеличивать и не уменьшать счетчик ссылок -- все равно они не имеют значения.

Undestroyable Retain
	return self

Undestroyable Release
	return self

Undestroyable Autorelease
	return self


Undestroyable Clone
	return self
