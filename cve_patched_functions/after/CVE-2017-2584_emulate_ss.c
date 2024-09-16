static int emulate_ss(struct x86_emulate_ctxt *ctxt, int err)
{
	return emulate_exception(ctxt, SS_VECTOR, err, true);
}
