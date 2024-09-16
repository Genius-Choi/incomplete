static struct in_ifaddr *find_matching_ifa(struct in_ifaddr *ifa)
{
	struct in_device *in_dev = ifa->ifa_dev;
	struct in_ifaddr *ifa1, **ifap;

	if (!ifa->ifa_local)
		return NULL;

	for (ifap = &in_dev->ifa_list; (ifa1 = *ifap) != NULL;
	     ifap = &ifa1->ifa_next) {
		if (ifa1->ifa_mask == ifa->ifa_mask &&
		    inet_ifa_match(ifa1->ifa_address, ifa) &&
		    ifa1->ifa_local == ifa->ifa_local)
			return ifa1;
	}
	return NULL;
}
