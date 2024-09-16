static int init_subctxts(struct hfi1_ctxtdata *uctxt,
			 const struct hfi1_user_info *uinfo)
{
	unsigned num_subctxts;

	num_subctxts = uinfo->subctxt_cnt;
	if (num_subctxts > HFI1_MAX_SHARED_CTXTS)
		return -EINVAL;

	uctxt->subctxt_cnt = uinfo->subctxt_cnt;
	uctxt->subctxt_id = uinfo->subctxt_id;
	uctxt->active_slaves = 1;
	uctxt->redirect_seq_cnt = 1;
	set_bit(HFI1_CTXT_MASTER_UNINIT, &uctxt->event_flags);

	return 0;
}
