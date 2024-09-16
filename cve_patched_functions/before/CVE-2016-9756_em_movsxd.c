static int em_movsxd(struct x86_emulate_ctxt *ctxt)
{
	ctxt->dst.val = (s32) ctxt->src.val;
	return X86EMUL_CONTINUE;
}
