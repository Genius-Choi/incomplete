static int segmented_read(struct x86_emulate_ctxt *ctxt,
			  struct segmented_address addr,
			  void *data,
			  unsigned size)
{
	int rc;
	ulong linear;

	rc = linearize(ctxt, addr, size, false, &linear);
	if (rc != X86EMUL_CONTINUE)
		return rc;
	return read_emulated(ctxt, linear, data, size);
}
