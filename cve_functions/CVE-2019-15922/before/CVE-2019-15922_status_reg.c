static inline int status_reg(struct pf_unit *pf)
{
	return pi_read_regr(pf->pi, 1, 6);
}
