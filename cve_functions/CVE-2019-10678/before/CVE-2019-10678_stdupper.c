void stdupper(std::string &inoutstring)
{
	for (size_t i = 0; i < inoutstring.size(); ++i)
		inoutstring[i] = toupper(inoutstring[i]);
}
