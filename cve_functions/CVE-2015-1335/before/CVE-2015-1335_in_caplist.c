int in_caplist(int cap, struct lxc_list *caps)
{
	struct lxc_list *iterator;
	int capid;

	lxc_list_for_each(iterator, caps) {
		capid = parse_cap(iterator->elem);
		if (capid == cap)
			return 1;
	}

	return 0;
}
