static int pf_reset(struct pf_unit *pf)
{
	int i, k, flg;
	int expect[5] = { 1, 1, 1, 0x14, 0xeb };

	pi_connect(pf->pi);
	write_reg(pf, 6, 0xa0+0x10*pf->drive);
	write_reg(pf, 7, 8);

	pf_sleep(20 * HZ / 1000);

	k = 0;
	while ((k++ < PF_RESET_TMO) && (status_reg(pf) & STAT_BUSY))
		pf_sleep(HZ / 10);

	flg = 1;
	for (i = 0; i < 5; i++)
		flg &= (read_reg(pf, i + 1) == expect[i]);

	if (verbose) {
		printk("%s: Reset (%d) signature = ", pf->name, k);
		for (i = 0; i < 5; i++)
			printk("%3x", read_reg(pf, i + 1));
		if (!flg)
			printk(" (incorrect)");
		printk("\n");
	}

	pi_disconnect(pf->pi);
	return flg - 1;
}
