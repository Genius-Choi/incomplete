static int set_ctxt_pkey(struct hfi1_ctxtdata *uctxt, unsigned subctxt,
			 u16 pkey)
{
	int ret = -ENOENT, i, intable = 0;
	struct hfi1_pportdata *ppd = uctxt->ppd;
	struct hfi1_devdata *dd = uctxt->dd;

	if (pkey == LIM_MGMT_P_KEY || pkey == FULL_MGMT_P_KEY) {
		ret = -EINVAL;
		goto done;
	}

	for (i = 0; i < ARRAY_SIZE(ppd->pkeys); i++)
		if (pkey == ppd->pkeys[i]) {
			intable = 1;
			break;
		}

	if (intable)
		ret = hfi1_set_ctxt_pkey(dd, uctxt->ctxt, pkey);
done:
	return ret;
}
