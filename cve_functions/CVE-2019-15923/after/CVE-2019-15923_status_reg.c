static inline int status_reg(struct pcd_unit *cd)
{
	return pi_read_regr(cd->pi, 1, 6);
}
