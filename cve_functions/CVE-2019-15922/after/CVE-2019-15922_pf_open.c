static int pf_open(struct block_device *bdev, fmode_t mode)
{
	struct pf_unit *pf = bdev->bd_disk->private_data;
	int ret;

	mutex_lock(&pf_mutex);
	pf_identify(pf);

	ret = -ENODEV;
	if (pf->media_status == PF_NM)
		goto out;

	ret = -EROFS;
	if ((pf->media_status == PF_RO) && (mode & FMODE_WRITE))
		goto out;

	ret = 0;
	pf->access++;
	if (pf->removable)
		pf_lock(pf, 1);
out:
	mutex_unlock(&pf_mutex);
	return ret;
}
