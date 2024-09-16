static struct in_ifaddr *inet_alloc_ifa(void)
{
	return kzalloc(sizeof(struct in_ifaddr), GFP_KERNEL);
}
