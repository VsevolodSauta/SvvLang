<Logic> placeHolder

@yes
@no
@true
@false

Logic Clone
	return self

Logic DeepClone
	return self

Logic Destroy
	return self

Logic <Comparison> Compare <Logic> arg
	if self Is arg
		return equal
	if self Is yes
		return greater
	return less

Logic <Logic> Sheffer <Logic> arg
	if self NotIs false
		if arg NotIs false
			return false
	return true

Logic <Logic> And (& &&) <Logic> arg
	if self NotIs false
		if arg NotIs false
			return true
	return false

Logic <Logic> Or (| ||) <Logic> arg
	if self NotIs false
		return true
	if arg NotIs false
		return true
	return false

Logic <Logic> Not (!)
	if self NotIs false
		return false
	return true

Logic <Logic> Xor (^) <Logic> arg
	if self NotIs false
		if arg NotIs false
			return false
		else
			return true
	else
		if arg NotIs false
			return true
		else
			return false
