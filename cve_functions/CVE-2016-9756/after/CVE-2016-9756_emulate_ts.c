static int emulate_ts(struct x86_emulate_ctxt *ctxt, int err)
{
	return emulate_exception(ctxt, TS_VECTOR, err, true);
}
