static int emulate_ud(struct x86_emulate_ctxt *ctxt)
{
	return emulate_exception(ctxt, UD_VECTOR, 0, false);
}
