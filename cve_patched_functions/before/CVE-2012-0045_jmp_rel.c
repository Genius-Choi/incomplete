static inline void jmp_rel(struct x86_emulate_ctxt *ctxt, int rel)
{
	register_address_increment(ctxt, &ctxt->_eip, rel);
}
