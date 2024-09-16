static int set_tcb_rpl(struct t3cdev *tdev, struct sk_buff *skb, void *ctx)
{
	struct cpl_set_tcb_rpl *rpl = cplhdr(skb);

	if (rpl->status != CPL_ERR_NONE) {
		printk(KERN_ERR MOD "Unexpected SET_TCB_RPL status %u "
		       "for tid %u\n", rpl->status, GET_TID(rpl));
	}
	return CPL_RET_BUF_DONE;
}
