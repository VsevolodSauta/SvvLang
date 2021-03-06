<Char@Object> <Number> [Clone] code

Char Init
	self.code = 0
	return self

Char <Comparison> CompareSameGID <Char> char
	return self.code ? char.code

Char Destroy
	self.code Release
	return super Destroy

Char Clone
	toReturn = <Char>
	toReturn SetCode self.code
	return toReturn

Char DeepClone
	toReturn = <Char>
	toReturn SetCode self.code
	return toReturn

Char SetCode <Number> code
	self.code Set code
	return self

Char <Number> GetCode (GetImmutableCode)
	return (self.code Clone) Autorelease

Char <Number> GetMutableCode
	return self.code

Char <Logic> IsSpace
	return self.code == 32

Char <Logic> IsWhiteSpace
	return self.code <= 32

Char <Logic> IsDigit
	return (self.code >= 48) And (self.code < 58)

Char <Logic> IsHexDigit
	return (self IsDigit) Or (((self.code >= 97) And (self.code <= 102)) Or ((self.code >= 65) And (self.code  <= 70)))
