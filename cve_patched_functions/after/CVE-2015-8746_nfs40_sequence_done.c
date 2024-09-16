static int nfs40_sequence_done(struct rpc_task *task,
			       struct nfs4_sequence_res *res)
{
	struct nfs4_slot *slot = res->sr_slot;
	struct nfs4_slot_table *tbl;

	if (slot == NULL)
		goto out;

	tbl = slot->table;
	spin_lock(&tbl->slot_tbl_lock);
	if (!nfs41_wake_and_assign_slot(tbl, slot))
		nfs4_free_slot(tbl, slot);
	spin_unlock(&tbl->slot_tbl_lock);

	res->sr_slot = NULL;
out:
	return 1;
}
