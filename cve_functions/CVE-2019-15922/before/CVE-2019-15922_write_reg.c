static inline void write_reg(struct pf_unit *pf, int reg, int val)
{
	pi_write_regr(pf->pi, 0, reg, val);
}
