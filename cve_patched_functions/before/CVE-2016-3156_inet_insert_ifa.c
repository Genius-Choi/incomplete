static int inet_insert_ifa(struct in_ifaddr *ifa)
{
	return __inet_insert_ifa(ifa, NULL, 0);
}
