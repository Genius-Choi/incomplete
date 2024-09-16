static int pcd_completion(struct pcd_unit *cd, char *buf, char *fun)
{
	int r, d, p, n, k, j;

	r = -1;
	k = 0;
	j = 0;

	if (!pcd_wait(cd, IDE_BUSY, IDE_DRQ | IDE_READY | IDE_ERR,
		      fun, "completion")) {
		r = 0;
		while (read_reg(cd, 7) & IDE_DRQ) {
			d = read_reg(cd, 4) + 256 * read_reg(cd, 5);
			n = (d + 3) & 0xfffc;
			p = read_reg(cd, 2) & 3;

			if ((p == 2) && (n > 0) && (j == 0)) {
				pi_read_block(cd->pi, buf, n);
				if (verbose > 1)
					printk("%s: %s: Read %d bytes\n",
					       cd->name, fun, n);
				r = 0;
				j++;
			} else {
				if (verbose > 1)
					printk
					    ("%s: %s: Unexpected phase %d, d=%d, k=%d\n",
					     cd->name, fun, p, d, k);
				if (verbose < 2)
					printk_once(
					    "%s: WARNING: ATAPI phase errors\n",
					    cd->name);
				mdelay(1);
			}
			if (k++ > PCD_TMO) {
				printk("%s: Stuck DRQ\n", cd->name);
				break;
			}
			if (pcd_wait
			    (cd, IDE_BUSY, IDE_DRQ | IDE_READY | IDE_ERR, fun,
			     "completion")) {
				r = -1;
				break;
			}
		}
	}

	pi_disconnect(cd->pi);

	return r;
}
