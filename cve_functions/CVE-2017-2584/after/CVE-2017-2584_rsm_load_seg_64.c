static int rsm_load_seg_64(struct x86_emulate_ctxt *ctxt, u64 smbase, int n)
{
	struct desc_struct desc;
	int offset;
	u16 selector;
	u32 base3;

	offset = 0x7e00 + n * 16;

	selector =                GET_SMSTATE(u16, smbase, offset);
	rsm_set_desc_flags(&desc, GET_SMSTATE(u16, smbase, offset + 2) << 8);
	set_desc_limit(&desc,     GET_SMSTATE(u32, smbase, offset + 4));
	set_desc_base(&desc,      GET_SMSTATE(u32, smbase, offset + 8));
	base3 =                   GET_SMSTATE(u32, smbase, offset + 12);

	ctxt->ops->set_segment(ctxt, selector, &desc, base3, n);
	return X86EMUL_CONTINUE;
}
