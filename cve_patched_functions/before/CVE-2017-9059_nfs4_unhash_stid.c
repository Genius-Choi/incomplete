void nfs4_unhash_stid(struct nfs4_stid *s)
{
	s->sc_type = 0;
}
