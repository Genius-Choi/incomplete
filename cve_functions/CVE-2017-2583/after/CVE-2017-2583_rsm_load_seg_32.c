static int rsm_load_seg_32(struct x86_emulate_ctxt *ctxt, u64 smbase, int n)
{
	struct desc_struct desc;
	int offset;
	u16 selector;

	selector = GET_SMSTATE(u32, smbase, 0x7fa8 + n * 4);

	if (n < 3)
		offset = 0x7f84 + n * 12;
	else
		offset = 0x7f2c + (n - 3) * 12;

	set_desc_base(&desc,      GET_SMSTATE(u32, smbase, offset + 8));
	set_desc_limit(&desc,     GET_SMSTATE(u32, smbase, offset + 4));
	rsm_set_desc_flags(&desc, GET_SMSTATE(u32, smbase, offset));
	ctxt->ops->set_segment(ctxt, selector, &desc, 0, n);
	return X86EMUL_CONTINUE;
}
