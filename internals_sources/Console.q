<Console> <File> toRead <File> toWrite

Console Init
	self.toRead = <File>
	self.toWrite = <File>
	return self

Console WriteLnString (PrintLnString) <List> string
	self.toWrite WriteLnString string
	return self

Console WriteString (PrintString) <List> string
	self.toWrite WriteNakedString string
	return self

Console WriteLnNumber (PrintLnNumber) <Number> number
	self.toWrite WriteLnNumber number
	return self

Console Clone
	return self

Console Compare <Console> console
	return equal

Console Destroy
	return self
