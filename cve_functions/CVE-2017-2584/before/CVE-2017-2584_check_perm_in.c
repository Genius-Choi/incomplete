static int check_perm_in(struct x86_emulate_ctxt *ctxt)
{
	ctxt->dst.bytes = min(ctxt->dst.bytes, 4u);
	if (!emulator_io_permited(ctxt, ctxt->src.val, ctxt->dst.bytes))
		return emulate_gp(ctxt, 0);

	return X86EMUL_CONTINUE;
}
