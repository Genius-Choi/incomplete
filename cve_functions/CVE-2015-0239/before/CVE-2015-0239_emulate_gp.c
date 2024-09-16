static int emulate_gp(struct x86_emulate_ctxt *ctxt, int err)
{
	return emulate_exception(ctxt, GP_VECTOR, err, true);
}
