static int emulate_de(struct x86_emulate_ctxt *ctxt)
{
	return emulate_exception(ctxt, DE_VECTOR, 0, false);
}
