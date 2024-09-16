static int em_pushf(struct x86_emulate_ctxt *ctxt)
{
	ctxt->src.val =  (unsigned long)ctxt->eflags;
	return em_push(ctxt);
}
