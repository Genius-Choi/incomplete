static int do_insn_fetch_byte(struct x86_emulate_ctxt *ctxt, u8 *dest)
{
	struct fetch_cache *fc = &ctxt->fetch;
	int rc;
	int size, cur_size;

	if (ctxt->_eip == fc->end) {
		unsigned long linear;
		struct segmented_address addr = { .seg = VCPU_SREG_CS,
						  .ea  = ctxt->_eip };
		cur_size = fc->end - fc->start;
		size = min(15UL - cur_size,
			   PAGE_SIZE - offset_in_page(ctxt->_eip));
		rc = __linearize(ctxt, addr, size, false, true, &linear);
		if (unlikely(rc != X86EMUL_CONTINUE))
			return rc;
		rc = ctxt->ops->fetch(ctxt, linear, fc->data + cur_size,
				      size, &ctxt->exception);
		if (unlikely(rc != X86EMUL_CONTINUE))
			return rc;
		fc->end += size;
	}
	*dest = fc->data[ctxt->_eip - fc->start];
	ctxt->_eip++;
	return X86EMUL_CONTINUE;
}
