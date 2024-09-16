static int pf_ioctl(struct block_device *bdev, fmode_t mode, unsigned int cmd, unsigned long arg)
{
	struct pf_unit *pf = bdev->bd_disk->private_data;

	if (cmd != CDROMEJECT)
		return -EINVAL;

	if (pf->access != 1)
		return -EBUSY;
	mutex_lock(&pf_mutex);
	pf_eject(pf);
	mutex_unlock(&pf_mutex);

	return 0;
}
