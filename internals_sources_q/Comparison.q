<Comparison> placeHolder

@greater
@uncomparableGreater
@equal
@uncomparableLess
@less

Comparison <Comparison> Clone
	return self

Comparison <Comparison> DeepClone
	return self

Comparison <Comparison> Destroy
	return self

Comparison <Comparison> Compare <Comparison> arg
	if self Is arg
		return equal
	
	if self Is greater
		return greater
	
	if self Is uncomparableGreater
		if arg Is greater
			return less
		else
			return greater
	
	if self Is equal
		if (arg Is greater) Or (arg Is uncomparableGreater)
			return less
		else
			return greater
	
	if self Is uncomparableLess
		if arg Is less
			return greater
		else
			return less
	
	if self Is less
		return less
	
	return nil
