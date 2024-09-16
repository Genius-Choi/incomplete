static inline void write_reg(struct pcd_unit *cd, int reg, int val)
{
	pi_write_regr(cd->pi, 0, reg, val);
}
