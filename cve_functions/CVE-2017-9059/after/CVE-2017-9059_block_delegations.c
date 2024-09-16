static void block_delegations(struct knfsd_fh *fh)
{
	u32 hash;
	struct bloom_pair *bd = &blocked_delegations;

	hash = jhash(&fh->fh_base, fh->fh_size, 0);

	spin_lock(&blocked_delegations_lock);
	__set_bit(hash&255, bd->set[bd->new]);
	__set_bit((hash>>8)&255, bd->set[bd->new]);
	__set_bit((hash>>16)&255, bd->set[bd->new]);
	if (bd->entries == 0)
		bd->swap_time = seconds_since_boot();
	bd->entries += 1;
	spin_unlock(&blocked_delegations_lock);
}
