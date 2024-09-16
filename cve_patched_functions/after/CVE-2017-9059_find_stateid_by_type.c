find_stateid_by_type(struct nfs4_client *cl, stateid_t *t, char typemask)
{
	struct nfs4_stid *s;

	spin_lock(&cl->cl_lock);
	s = find_stateid_locked(cl, t);
	if (s != NULL) {
		if (typemask & s->sc_type)
			atomic_inc(&s->sc_count);
		else
			s = NULL;
	}
	spin_unlock(&cl->cl_lock);
	return s;
}
