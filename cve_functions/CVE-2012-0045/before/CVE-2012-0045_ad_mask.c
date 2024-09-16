static inline unsigned long ad_mask(struct x86_emulate_ctxt *ctxt)
{
	return (1UL << (ctxt->ad_bytes << 3)) - 1;
}
