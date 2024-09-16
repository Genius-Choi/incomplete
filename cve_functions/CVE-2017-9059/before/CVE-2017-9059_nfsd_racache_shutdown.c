nfsd_racache_shutdown(void)
{
	struct raparms *raparm, *last_raparm;
	unsigned int i;

	dprintk("nfsd: freeing readahead buffers.\n");

	for (i = 0; i < RAPARM_HASH_SIZE; i++) {
		raparm = raparm_hash[i].pb_head;
		while(raparm) {
			last_raparm = raparm;
			raparm = raparm->p_next;
			kfree(last_raparm);
		}
		raparm_hash[i].pb_head = NULL;
	}
}
