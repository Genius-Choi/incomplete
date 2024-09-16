void nfsd_put_raparams(struct file *file, struct raparms *ra)
{
	struct raparm_hbucket *rab = &raparm_hash[ra->p_hindex];

	spin_lock(&rab->pb_lock);
	ra->p_ra = file->f_ra;
	ra->p_set = 1;
	ra->p_count--;
	spin_unlock(&rab->pb_lock);
}
