<Token> <Number> [Retain] typeQualifier [Retain] entity

Token Init
	self.typeQualifier = 0
	return self

Token <Comparation> Compare <Token> token
	candidate = self.typeQualifier ? token.typeQualifier
	if candidate == equal
		if self HasNil
			return equal
		if self HasNumber
			return (self.entity AsNumber) ? (token.entity AsNumber)
		if self HasString
			return (self.entity AsList) ? (token.entity AsList)
		if self HasObject
			return (self.entity AsListMap) ? (token.entity AsListMap)
		return equal
	else
		return candidate

Token Destroy
	self.typeQualifier Release
	return self Destroy

Token HasNil
	return self.typeQualifier == 0

Token HasNumber
	return self.typeQualifier == 1

Token HasString
	return self.typeQualifier == 2

Token HasObject
	return self.typeQualifier == 100

Token SetNil
	self.typeQualifier = 0
	self.entity = nil
	return self

Token SetNumber <Number> number
	self.typeQualifier = 1
	self.entity = number
	return self

Token SetString <List> string
	self.typeQualifier = 2
	self.entity = string
	return self

Token SetObject <ListMap> object
	self.typeQualifier = 100
	self.entity = object
	return self

