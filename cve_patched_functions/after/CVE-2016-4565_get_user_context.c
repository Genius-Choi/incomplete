static int get_user_context(struct file *fp, struct hfi1_user_info *uinfo,
			    int devno, unsigned alg)
{
	struct hfi1_devdata *dd = NULL;
	int ret = 0, devmax, npresent, nup, dev;

	devmax = hfi1_count_units(&npresent, &nup);
	if (!npresent) {
		ret = -ENXIO;
		goto done;
	}
	if (!nup) {
		ret = -ENETDOWN;
		goto done;
	}
	if (devno >= 0) {
		dd = hfi1_lookup(devno);
		if (!dd)
			ret = -ENODEV;
		else if (!dd->freectxts)
			ret = -EBUSY;
	} else {
		struct hfi1_devdata *pdd;

		if (alg == HFI1_ALG_ACROSS) {
			unsigned free = 0U;

			for (dev = 0; dev < devmax; dev++) {
				pdd = hfi1_lookup(dev);
				if (!pdd)
					continue;
				if (!usable_device(pdd))
					continue;
				if (pdd->freectxts &&
				    pdd->freectxts > free) {
					dd = pdd;
					free = pdd->freectxts;
				}
			}
		} else {
			for (dev = 0; dev < devmax; dev++) {
				pdd = hfi1_lookup(dev);
				if (!pdd)
					continue;
				if (!usable_device(pdd))
					continue;
				if (pdd->freectxts) {
					dd = pdd;
					break;
				}
			}
		}
		if (!dd)
			ret = -EBUSY;
	}
done:
	return ret ? ret : allocate_ctxt(fp, dd, uinfo);
}
