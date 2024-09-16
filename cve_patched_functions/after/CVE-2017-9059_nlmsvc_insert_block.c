static void nlmsvc_insert_block(struct nlm_block *block, unsigned long when)
{
	spin_lock(&nlm_blocked_lock);
	nlmsvc_insert_block_locked(block, when);
	spin_unlock(&nlm_blocked_lock);
}
