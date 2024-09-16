nfs4_find_slot(struct nfs4_slot_table *tbl)
{
	int slotid;
	u8 ret_id = NFS4_MAX_SLOT_TABLE;
	BUILD_BUG_ON((u8)NFS4_MAX_SLOT_TABLE != (int)NFS4_MAX_SLOT_TABLE);

	dprintk("--> %s used_slots=%04lx highest_used=%d max_slots=%d\n",
		__func__, tbl->used_slots[0], tbl->highest_used_slotid,
		tbl->max_slots);
	slotid = find_first_zero_bit(tbl->used_slots, tbl->max_slots);
	if (slotid >= tbl->max_slots)
		goto out;
	__set_bit(slotid, tbl->used_slots);
	if (slotid > tbl->highest_used_slotid)
		tbl->highest_used_slotid = slotid;
	ret_id = slotid;
out:
	dprintk("<-- %s used_slots=%04lx highest_used=%d slotid=%d \n",
		__func__, tbl->used_slots[0], tbl->highest_used_slotid, ret_id);
	return ret_id;
}
