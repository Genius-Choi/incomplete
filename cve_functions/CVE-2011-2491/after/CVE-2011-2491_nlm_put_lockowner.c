static void nlm_put_lockowner(struct nlm_lockowner *lockowner)
{
	if (!atomic_dec_and_lock(&lockowner->count, &lockowner->host->h_lock))
		return;
	list_del(&lockowner->list);
	spin_unlock(&lockowner->host->h_lock);
	nlmclnt_release_host(lockowner->host);
	kfree(lockowner);
}
