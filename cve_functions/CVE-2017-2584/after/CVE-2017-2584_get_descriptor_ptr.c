static int get_descriptor_ptr(struct x86_emulate_ctxt *ctxt,
			      u16 selector, ulong *desc_addr_p)
{
	struct desc_ptr dt;
	u16 index = selector >> 3;
	ulong addr;

	get_descriptor_table_ptr(ctxt, selector, &dt);

	if (dt.size < index * 8 + 7)
		return emulate_gp(ctxt, selector & 0xfffc);

	addr = dt.address + index * 8;

#ifdef CONFIG_X86_64
	if (addr >> 32 != 0) {
		u64 efer = 0;

		ctxt->ops->get_msr(ctxt, MSR_EFER, &efer);
		if (!(efer & EFER_LMA))
			addr &= (u32)-1;
	}
#endif

	*desc_addr_p = addr;
	return X86EMUL_CONTINUE;
}
