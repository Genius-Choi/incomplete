family_str(int family)
{
	if (family == AF_INET)
		return "IPv4";
	if (family == AF_INET6)
		return "IPv6";
	return "None";
}
