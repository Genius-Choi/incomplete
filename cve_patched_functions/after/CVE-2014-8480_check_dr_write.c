static int check_dr_write(struct x86_emulate_ctxt *ctxt)
{
	u64 new_val = ctxt->src.val64;
	int dr = ctxt->modrm_reg;

	if ((dr == 6 || dr == 7) && (new_val & 0xffffffff00000000ULL))
		return emulate_gp(ctxt, 0);

	return check_dr_read(ctxt);
}
