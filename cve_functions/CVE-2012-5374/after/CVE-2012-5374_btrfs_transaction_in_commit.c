int btrfs_transaction_in_commit(struct btrfs_fs_info *info)
{
	int ret = 0;
	spin_lock(&info->trans_lock);
	if (info->running_transaction)
		ret = info->running_transaction->in_commit;
	spin_unlock(&info->trans_lock);
	return ret;
}
