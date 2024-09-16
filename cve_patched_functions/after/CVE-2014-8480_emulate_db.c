static int emulate_db(struct x86_emulate_ctxt *ctxt)
{
	return emulate_exception(ctxt, DB_VECTOR, 0, false);
}
