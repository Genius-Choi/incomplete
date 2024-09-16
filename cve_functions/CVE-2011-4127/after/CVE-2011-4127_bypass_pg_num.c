static int bypass_pg_num(struct multipath *m, const char *pgstr, int bypassed)
{
	struct priority_group *pg;
	unsigned pgnum;

	if (!pgstr || (sscanf(pgstr, "%u", &pgnum) != 1) || !pgnum ||
	    (pgnum > m->nr_priority_groups)) {
		DMWARN("invalid PG number supplied to bypass_pg");
		return -EINVAL;
	}

	list_for_each_entry(pg, &m->priority_groups, list) {
		if (!--pgnum)
			break;
	}

	bypass_pg(m, pg, bypassed);
	return 0;
}
