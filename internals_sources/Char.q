<Char> <Number> [Clone] code

Char Init
	self.code = 0
	return self

Char <Comparation> Compare <Char> char
	return self.code ? char.code

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

