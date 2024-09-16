static int stack_size(struct x86_emulate_ctxt *ctxt)
{
	return (__fls(stack_mask(ctxt)) + 1) >> 3;
}
