void stdlower(std::string &inoutstring)
{
	std::transform(inoutstring.begin(), inoutstring.end(), inoutstring.begin(), ::tolower);
}
