static inline int read_reg(struct pf_unit *pf, int reg)
{
	return pi_read_regr(pf->pi, 0, reg);
}
