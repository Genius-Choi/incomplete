static void __user *get_addr_ref_32(struct insn *insn, struct pt_regs *regs)
{
	unsigned long linear_addr = -1L, seg_base, seg_limit;
	int eff_addr, regoff;
	long tmp;
	int ret;

	if (insn->addr_bytes != 4)
		goto out;

	if (X86_MODRM_MOD(insn->modrm.value) == 3) {
		ret = get_eff_addr_reg(insn, regs, &regoff, &tmp);
		if (ret)
			goto out;

		eff_addr = tmp;

	} else {
		if (insn->sib.nbytes) {
			ret = get_eff_addr_sib(insn, regs, &regoff, &tmp);
			if (ret)
				goto out;

			eff_addr = tmp;
		} else {
			ret = get_eff_addr_modrm(insn, regs, &regoff, &tmp);
			if (ret)
				goto out;

			eff_addr = tmp;
		}
	}

	ret = get_seg_base_limit(insn, regs, regoff, &seg_base, &seg_limit);
	if (ret)
		goto out;

	/*
	 * In protected mode, before computing the linear address, make sure
	 * the effective address is within the limits of the segment.
	 * 32-bit addresses can be used in long and virtual-8086 modes if an
	 * address override prefix is used. In such cases, segment limits are
	 * not enforced. When in virtual-8086 mode, the segment limit is -1L
	 * to reflect this situation.
	 *
	 * After computed, the effective address is treated as an unsigned
	 * quantity.
	 */
	if (!user_64bit_mode(regs) && ((unsigned int)eff_addr > seg_limit))
		goto out;

	/*
	 * Even though 32-bit address encodings are allowed in virtual-8086
	 * mode, the address range is still limited to [0x-0xffff].
	 */
	if (v8086_mode(regs) && (eff_addr & ~0xffff))
		goto out;

	/*
	 * Data type long could be 64 bits in size. Ensure that our 32-bit
	 * effective address is not sign-extended when computing the linear
	 * address.
	 */
	linear_addr = (unsigned long)(eff_addr & 0xffffffff) + seg_base;

	/* Limit linear address to 20 bits */
	if (v8086_mode(regs))
		linear_addr &= 0xfffff;

out:
	return (void __user *)linear_addr;
}
