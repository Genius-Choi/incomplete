static inline int nlm_pidbusy(struct nlm_host *host, uint32_t pid)
{
	struct nlm_lockowner *lockowner;
	list_for_each_entry(lockowner, &host->h_lockowners, list) {
		if (lockowner->pid == pid)
			return -EBUSY;
	}
	return 0;
}
