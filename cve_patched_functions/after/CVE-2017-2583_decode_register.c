static void *decode_register(struct x86_emulate_ctxt *ctxt, u8 modrm_reg,
			     int byteop)
{
	void *p;
	int highbyte_regs = (ctxt->rex_prefix == 0) && byteop;

	if (highbyte_regs && modrm_reg >= 4 && modrm_reg < 8)
		p = (unsigned char *)reg_rmw(ctxt, modrm_reg & 3) + 1;
	else
		p = reg_rmw(ctxt, modrm_reg);
	return p;
}
