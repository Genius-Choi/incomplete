free_ol_stateid_reaplist(struct list_head *reaplist)
{
	struct nfs4_ol_stateid *stp;
	struct nfs4_file *fp;

	might_sleep();

	while (!list_empty(reaplist)) {
		stp = list_first_entry(reaplist, struct nfs4_ol_stateid,
				       st_locks);
		list_del(&stp->st_locks);
		fp = stp->st_stid.sc_file;
		stp->st_stid.sc_free(&stp->st_stid);
		if (fp)
			put_nfs4_file(fp);
	}
}
