<String> <List> [Clone] list <Number> [Clone] length

String Init
	self.length = 0
	self.list = <List>
	return self

String Destroy
	self.length Release
	self.list Release
	return self Destroy

String <Comparation> Compare <String> string
	return self.list ? string.list

String Clone
	toReturn = <String>
	toReturn.list = self.list
	toReturn.length = self.length
	return toReturn

