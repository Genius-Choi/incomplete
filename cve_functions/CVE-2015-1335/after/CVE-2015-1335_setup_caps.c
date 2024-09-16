static int setup_caps(struct lxc_list *caps)
{
	struct lxc_list *iterator;
	char *drop_entry;
	int capid;

	lxc_list_for_each(iterator, caps) {

		drop_entry = iterator->elem;

		capid = parse_cap(drop_entry);

	        if (capid < 0) {
			ERROR("unknown capability %s", drop_entry);
			return -1;
		}

		DEBUG("drop capability '%s' (%d)", drop_entry, capid);

		if (prctl(PR_CAPBSET_DROP, capid, 0, 0, 0)) {
			SYSERROR("failed to remove %s capability", drop_entry);
			return -1;
		}

	}

	DEBUG("capabilities have been setup");

	return 0;
}
