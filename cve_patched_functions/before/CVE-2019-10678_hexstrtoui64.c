uint64_t hexstrtoui64(const std::string &str)
{
	uint64_t ul;
	std::stringstream ss;
	ss << std::hex << str;
	ss >> ul;
	return ul;
}
