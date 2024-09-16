static int em_invlpg(struct x86_emulate_ctxt *ctxt)
{
	int rc;
	ulong linear;

	rc = linearize(ctxt, ctxt->src.addr.mem, 1, false, &linear);
	if (rc == X86EMUL_CONTINUE)
		ctxt->ops->invlpg(ctxt, linear);
	/* Disable writeback. */
	ctxt->dst.type = OP_NONE;
	return X86EMUL_CONTINUE;
}
