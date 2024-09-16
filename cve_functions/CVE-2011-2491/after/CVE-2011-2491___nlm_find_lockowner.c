static struct nlm_lockowner *__nlm_find_lockowner(struct nlm_host *host, fl_owner_t owner)
{
	struct nlm_lockowner *lockowner;
	list_for_each_entry(lockowner, &host->h_lockowners, list) {
		if (lockowner->owner != owner)
			continue;
		return nlm_get_lockowner(lockowner);
	}
	return NULL;
}
