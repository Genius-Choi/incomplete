static int choose_port_ctxt(struct file *fp, struct qib_devdata *dd, u32 port,
			    const struct qib_user_info *uinfo)
{
	struct qib_pportdata *ppd = NULL;
	int ret, ctxt;

	if (port) {
		if (!usable(dd->pport + port - 1)) {
			ret = -ENETDOWN;
			goto done;
		} else
			ppd = dd->pport + port - 1;
	}
	for (ctxt = dd->first_user_ctxt; ctxt < dd->cfgctxts && dd->rcd[ctxt];
	     ctxt++)
		;
	if (ctxt == dd->cfgctxts) {
		ret = -EBUSY;
		goto done;
	}
	if (!ppd) {
		u32 pidx = ctxt % dd->num_pports;

		if (usable(dd->pport + pidx))
			ppd = dd->pport + pidx;
		else {
			for (pidx = 0; pidx < dd->num_pports && !ppd;
			     pidx++)
				if (usable(dd->pport + pidx))
					ppd = dd->pport + pidx;
		}
	}
	ret = ppd ? setup_ctxt(ppd, ctxt, fp, uinfo) : -ENETDOWN;
done:
	return ret;
}
