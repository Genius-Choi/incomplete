bool x86_page_table_writing_insn(struct x86_emulate_ctxt *ctxt)
{
	return ctxt->d & PageTable;
}
