reaper(void)
{
	time_t deadline = 0, now = monotime();
	Identity *id, *nxt;
	int version;
	Idtab *tab;

	for (version = 1; version < 3; version++) {
		tab = idtab_lookup(version);
		for (id = TAILQ_FIRST(&tab->idlist); id; id = nxt) {
			nxt = TAILQ_NEXT(id, next);
			if (id->death == 0)
				continue;
			if (now >= id->death) {
				debug("expiring key '%s'", id->comment);
				TAILQ_REMOVE(&tab->idlist, id, next);
				free_identity(id);
				tab->nentries--;
			} else
				deadline = (deadline == 0) ? id->death :
				    MINIMUM(deadline, id->death);
		}
	}
	if (deadline == 0 || deadline <= now)
		return 0;
	else
		return (deadline - now);
}
