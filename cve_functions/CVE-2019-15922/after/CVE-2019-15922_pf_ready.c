static int pf_ready(void)
{
	return (((status_reg(pf_current) & (STAT_BUSY | pf_mask)) == pf_mask));
}
