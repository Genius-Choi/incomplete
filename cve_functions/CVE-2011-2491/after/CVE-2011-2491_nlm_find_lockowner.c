static struct nlm_lockowner *nlm_find_lockowner(struct nlm_host *host, fl_owner_t owner)
{
	struct nlm_lockowner *res, *new = NULL;

	spin_lock(&host->h_lock);
	res = __nlm_find_lockowner(host, owner);
	if (res == NULL) {
		spin_unlock(&host->h_lock);
		new = kmalloc(sizeof(*new), GFP_KERNEL);
		spin_lock(&host->h_lock);
		res = __nlm_find_lockowner(host, owner);
		if (res == NULL && new != NULL) {
			res = new;
			atomic_set(&new->count, 1);
			new->owner = owner;
			new->pid = __nlm_alloc_pid(host);
			new->host = nlm_get_host(host);
			list_add(&new->list, &host->h_lockowners);
			new = NULL;
		}
	}
	spin_unlock(&host->h_lock);
	kfree(new);
	return res;
}
