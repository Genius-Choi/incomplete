static int linearize(struct x86_emulate_ctxt *ctxt,
		     struct segmented_address addr,
		     unsigned size, bool write,
		     ulong *linear)
{
	unsigned max_size;
	return __linearize(ctxt, addr, &max_size, size, write, false,
			   ctxt->mode, linear);
}
