static bool insn_aligned(struct x86_emulate_ctxt *ctxt, unsigned size)
{
	if (likely(size < 16))
		return false;

	if (ctxt->d & Aligned)
		return true;
	else if (ctxt->d & Unaligned)
		return false;
	else if (ctxt->d & Avx)
		return false;
	else
		return true;
}
