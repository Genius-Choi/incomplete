void stdreplace(
	std::string &inoutstring,
	const std::string& replaceWhat,
	const std::string& replaceWithWhat)
{
	int pos = 0;
	while (std::string::npos != (pos = inoutstring.find(replaceWhat, pos)))
	{
		inoutstring.replace(pos, replaceWhat.size(), replaceWithWhat);
		pos += replaceWithWhat.size();
	}
}
