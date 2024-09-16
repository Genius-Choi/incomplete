static void pf_get_capacity(struct pf_unit *pf)
{
	char rc_cmd[12] = { ATAPI_CAPACITY, pf->lun << 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	char buf[8];
	int bs;

	if (pf_atapi(pf, rc_cmd, 8, buf, "get capacity")) {
		pf->media_status = PF_NM;
		return;
	}
	set_capacity(pf->disk, xl(buf, 0) + 1);
	bs = xl(buf, 4);
	if (bs != 512) {
		set_capacity(pf->disk, 0);
		if (verbose)
			printk("%s: Drive %d, LUN %d,"
			       " unsupported block size %d\n",
			       pf->name, pf->drive, pf->lun, bs);
	}
}
