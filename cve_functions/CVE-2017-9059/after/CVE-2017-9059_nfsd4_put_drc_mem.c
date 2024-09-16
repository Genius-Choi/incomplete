static void nfsd4_put_drc_mem(struct nfsd4_channel_attrs *ca)
{
	int slotsize = slot_bytes(ca);

	spin_lock(&nfsd_drc_lock);
	nfsd_drc_mem_used -= slotsize * ca->maxreqs;
	spin_unlock(&nfsd_drc_lock);
}
