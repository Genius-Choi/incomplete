static int em_push_sreg(struct x86_emulate_ctxt *ctxt)
{
	int seg = ctxt->src2.val;

	ctxt->src.val = get_segment_selector(ctxt, seg);

	return em_push(ctxt);
}
