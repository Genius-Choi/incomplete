void StringSplit(std::string str, const std::string &delim, std::vector<std::string> &results)
{
	results.clear();
	size_t cutAt;
	while( (cutAt = str.find(delim)) != std::string::npos )
	{
		results.push_back(str.substr(0,cutAt));
		str = str.substr(cutAt+ delim.size());
	}
	if (!str.empty())
	{
		results.push_back(str);
	}
}
