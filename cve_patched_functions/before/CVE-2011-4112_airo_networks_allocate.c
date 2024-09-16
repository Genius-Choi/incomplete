static int airo_networks_allocate(struct airo_info *ai)
{
	if (ai->networks)
		return 0;

	ai->networks = kcalloc(AIRO_MAX_NETWORK_COUNT, sizeof(BSSListElement),
			       GFP_KERNEL);
	if (!ai->networks) {
		airo_print_warn("", "Out of memory allocating beacons");
		return -ENOMEM;
	}

	return 0;
}
