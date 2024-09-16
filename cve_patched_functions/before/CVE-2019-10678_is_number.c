bool is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && (isdigit(*it) || (*it == '.') || (*it == '-') || (*it == ' ') || (*it == 0x00))) ++it;
	return !s.empty() && it == s.end();
}
