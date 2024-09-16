nfs4_inc_and_copy_stateid(stateid_t *dst, struct nfs4_stid *stid)
{
	stateid_t *src = &stid->sc_stateid;

	spin_lock(&stid->sc_lock);
	if (unlikely(++src->si_generation == 0))
		src->si_generation = 1;
	memcpy(dst, src, sizeof(*dst));
	spin_unlock(&stid->sc_lock);
}
