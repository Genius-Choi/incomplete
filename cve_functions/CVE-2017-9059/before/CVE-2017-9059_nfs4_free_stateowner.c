static inline void nfs4_free_stateowner(struct nfs4_stateowner *sop)
{
	kfree(sop->so_owner.data);
	sop->so_ops->so_free(sop);
}
