static void pf_release(struct gendisk *disk, fmode_t mode)
{
	struct pf_unit *pf = disk->private_data;

	mutex_lock(&pf_mutex);
	if (pf->access <= 0) {
		mutex_unlock(&pf_mutex);
		WARN_ON(1);
		return;
	}

	pf->access--;

	if (!pf->access && pf->removable)
		pf_lock(pf, 0);

	mutex_unlock(&pf_mutex);
}
