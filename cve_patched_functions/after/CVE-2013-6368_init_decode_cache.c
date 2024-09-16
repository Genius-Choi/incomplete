static void init_decode_cache(struct x86_emulate_ctxt *ctxt)
{
	memset(&ctxt->opcode_len, 0,
	       (void *)&ctxt->_regs - (void *)&ctxt->opcode_len);

	ctxt->fetch.start = 0;
	ctxt->fetch.end = 0;
	ctxt->io_read.pos = 0;
	ctxt->io_read.end = 0;
	ctxt->mem_read.pos = 0;
	ctxt->mem_read.end = 0;
}
