bool IsArgumentSecure(const std::string &arg)
{
	std::string larg(arg);
	std::transform(larg.begin(), larg.end(), larg.begin(), ::tolower);

	int ii = 0;
	while (szInsecureArgumentOptions[ii] != NULL)
	{
		if (larg.find(szInsecureArgumentOptions[ii]) != std::string::npos)
			return false;
		ii++;
	}
	return true;
}
