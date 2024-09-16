static u32 nfsd4_get_drc_mem(struct nfsd4_channel_attrs *ca)
{
	u32 slotsize = slot_bytes(ca);
	u32 num = ca->maxreqs;
	int avail;

	spin_lock(&nfsd_drc_lock);
	avail = min((unsigned long)NFSD_MAX_MEM_PER_SESSION,
		    nfsd_drc_max_mem - nfsd_drc_mem_used);
	num = min_t(int, num, avail / slotsize);
	nfsd_drc_mem_used += num * slotsize;
	spin_unlock(&nfsd_drc_lock);

	return num;
}
