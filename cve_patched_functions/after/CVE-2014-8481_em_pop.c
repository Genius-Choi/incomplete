static int em_pop(struct x86_emulate_ctxt *ctxt)
{
	return emulate_pop(ctxt, &ctxt->dst.val, ctxt->op_bytes);
}
