static int pf_completion(struct pf_unit *pf, char *buf, char *fun)
{
	int r, s, n;

	r = pf_wait(pf, STAT_BUSY, STAT_DRQ | STAT_READY | STAT_ERR,
		    fun, "completion");

	if ((read_reg(pf, 2) & 2) && (read_reg(pf, 7) & STAT_DRQ)) {
		n = (((read_reg(pf, 4) + 256 * read_reg(pf, 5)) +
		      3) & 0xfffc);
		pi_read_block(pf->pi, buf, n);
	}

	s = pf_wait(pf, STAT_BUSY, STAT_READY | STAT_ERR, fun, "data done");

	pi_disconnect(pf->pi);

	return (r ? r : s);
}
