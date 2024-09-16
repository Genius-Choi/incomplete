static void *dn_socket_get_idx(struct seq_file *seq, loff_t pos)
{
	void *rc;
	read_lock_bh(&dn_hash_lock);
	rc = socket_get_idx(seq, &pos);
	if (!rc) {
		read_unlock_bh(&dn_hash_lock);
	}
	return rc;
}
