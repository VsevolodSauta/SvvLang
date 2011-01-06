<JSON> null true false

JSON Init
	null = <Object>
	true = <Object>
	false = <Object>
	return self

JSON Compare <JSON> json
	return equal

JSON Clone
	return self

JSON Destroy
	null Release
	true Release
	false Release
	return self Destroy

JSON <List> ParseString <ListIterator> iterator
	iterator StringSkipWhiteSpace
	if (iterator ThisEnd) Or ((iterator ThisData) != '"')
		return nil
	iterator ++
	toReturn = <List>
	toReturn Autorelease
	while iterator NotThisEnd
		if (iterator ThisData) == '"'
			iterator ++
			return toReturn
		elif (iterator ThisData) == '\\'
			iterator ++
			if (iterator ThisData) == '"'
				toReturn PushBack '"'
			elif (iterator ThisData) == '\\'
				toReturn PushBack '\\'
			elif (iterator ThisData) == 't'
				toReturn PushBack '\t'
			elif (iterator ThisData) == 'b'
				toReturn PushBack '\b'
			elif (iterator ThisData) == 'f'
				toReturn PushBack '\f'
			elif (iterator ThisData) == '/'
				toReturn PushBack '/'
			elif (iterator ThisData) == 'n'
				toReturn PushBack '\n'
			elif (iterator ThisData) == 'r'
				toReturn PushBack '\r'
			elif (iterator ThisData) == 'u'
				hexNumberToParse = <List>
				iterator ++
				hexNumberToParse Append (iterator ThisData)
				iterator ++
				hexNumberToParse Append (iterator ThisData)
				iterator ++
				hexNumberToParse Append (iterator ThisData)
				iterator ++
				hexNumberToParse Append (iterator ThisData)
				char = <Char>
				char SetCode (numberFactory FromHexString hexNumberToParse)
				toReturn Append char
				char Release
		else
			toReturn Append (iterator ThisData)
		iterator ++
	return nil

JSON <ListMap> ParseObject <ListIterator> iterator
	iterator StringSkipWhiteSpace
	toReturn = <ListMap>
	toReturn Autorelease
	if (iterator ThisEnd) Or ((iterator ThisData) != '{')
		return nil
	iterator ++
	while iterator NotThisEnd
		iterator StringSkipWhiteSpace
		if (iterator ThisData) == '}'
			iterator ++
			return toReturn
		string = self ParseString iterator
		if string == nil
			return nil
		iterator StringSkipWhiteSpace
		if (iterator ThisData) != ':'
			return nil
		iterator ++
		value = self ParseValue iterator
		if value == nil
			return nil
		iterator StringSkipWhiteSpace
		toReturn AtPut string value
		if (iterator ThisData) == ','
			iterator ++
		elif (iterator ThisData) != '}'
			return nil
	return nil
	
JSON <List> ParseArray <ListIterator> iterator
	iterator StringSkipWhiteSpace
	toReturn = <List>
	toReturn Autorelease
	if (iterator ThisEnd) Or ((iterator ThisData) != '[')
		return nil
	iterator ++
	while iterator NotThisEnd
		iterator StringSkipWhiteSpace
		if (iterator ThisData) == ']'
			iterator ++
			return toReturn
		value = self ParseValue iterator
		if value == nil
			return nil
		iterator StringSkipWhiteSpace
		toReturn Append value
		if (iterator ThisData) == ','
			iterator ++
		elif (iterator ThisData) != ']'
			return nil
	return nil

JSON ParseValue <ListIterator> iterator
	iterator StringSkipWhiteSpace
	if iterator ThisEnd
		return nil
	elif (iterator ThisData) == '"'
		return self ParseString iterator
	elif (iterator ThisData) == '{'
		return self ParseObject iterator
	elif (iterator ThisData) == '['
		return self ParseArray iterator
	elif ((iterator ThisData) == '-') Or ((iterator CharData) IsDigit)
		return self ParseNumber iterator
	elif (iterator ThisData) == 't'
		return self ParseTrue iterator
	elif (iterator ThisData) == 'f'
		return self ParseFalse iterator
	elif (iterator ThisData) == 'n'
		return self ParseNull iterator
	else
		return nil

JSON ParseTrue <ListIterator> iterator
	if (iterator ThisData) != 't'
		return nil
	iterator ++
	if (iterator ThisData) != 'r'
		return nil
	iterator ++
	if (iterator ThisData) != 'u'
		return nil
	iterator ++
	if (iterator ThisData) != 'e'
		return nil
	iterator ++
	return self.true

JSON ParseFalse <ListIterator> iterator
	if (iterator ThisData) != 'f'
		return nil
	iterator ++
	if (iterator ThisData) != 'a'
		return nil
	iterator ++
	if (iterator ThisData) != 'l'
		return nil
	iterator ++
	if (iterator ThisData) != 's'
		return nil
	iterator ++
	if (iterator ThisData) != 'e'
		return nil
	iterator ++
	return self.false

JSON ParseNull <ListIterator> iterator
	if (iterator ThisData) != 'n'
		return nil
	iterator ++
	if (iterator ThisData) != 'u'
		return nil
	iterator ++
	if (iterator ThisData) != 'l'
		return nil
	iterator ++
	if (iterator ThisData) != 'l'
		return nil
	iterator ++
	return self.null

JSON ParseNumber <ListIterator> iterator
	iterator StringSkipWhiteSpace
	negative = false
	toReturn = 0
	if (iterator ThisData) == '-'
		negative = true
		iterator ++
	if (iterator CharData) NotIsDigit
		return nil
	while (iterator CharData) IsDigit
		toReturn *= 10
		toReturn += (((iterator CharData) GetCode) - 48)
		iterator ++
	if (iterator ThisData) == '.'
		iterator ++
		toDivide = 1
		while (iterator CharData) IsDigit
			toDivide *= 10
			toReturn += ((((iterator CharData) GetCode) - 48) / toDivide)
			iterator ++
	if ((iterator ThisData) == 'E') Or ((iterator ThisData) == 'e')
		iterator ++
		exp = 0
		while (iterator CharData) IsDigit
			exp *= 10
			exp += (((iterator CharData) GetCode) - 48)
			iterator ++
		toReturn * (10 ** exp)
	if negative
		return toReturn Inv
	else
		return toReturn
