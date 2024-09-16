static __always_inline int do_insn_fetch_bytes(struct x86_emulate_ctxt *ctxt,
					       unsigned size)
{
	if (unlikely(ctxt->fetch.end - ctxt->fetch.ptr < size))
		return __do_insn_fetch_bytes(ctxt, size);
	else
		return X86EMUL_CONTINUE;
}
