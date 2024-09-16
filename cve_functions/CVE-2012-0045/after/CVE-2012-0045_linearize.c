static int linearize(struct x86_emulate_ctxt *ctxt,
		     struct segmented_address addr,
		     unsigned size, bool write,
		     ulong *linear)
{
	return __linearize(ctxt, addr, size, write, false, linear);
}
