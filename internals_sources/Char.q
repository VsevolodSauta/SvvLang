<Char> <Number> code

Char Init
	self.code = 0 Retain
	return self

Char <Comparation> Compare <Char> char
	return self.code Compare char.code

Char <Object> Destroy
	self.code Release
	return (self AsObject) Destroy

Char Clone
	toReturn = <Char>
	toReturn SetCode self.code
	return toReturn

Char SetCode <Number> code
	self.code Set code
	return self

Char <Number> GetCode
	return self.code TempClone

