static int segmented_cmpxchg(struct x86_emulate_ctxt *ctxt,
			     struct segmented_address addr,
			     const void *orig_data, const void *data,
			     unsigned size)
{
	int rc;
	ulong linear;

	rc = linearize(ctxt, addr, size, true, &linear);
	if (rc != X86EMUL_CONTINUE)
		return rc;
	return ctxt->ops->cmpxchg_emulated(ctxt, linear, orig_data, data,
					   size, &ctxt->exception);
}
