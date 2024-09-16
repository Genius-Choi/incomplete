static void __user *get_addr_ref_64(struct insn *insn, struct pt_regs *regs)
{
	unsigned long linear_addr = -1L, seg_base;
	int regoff, ret;
	long eff_addr;

	if (insn->addr_bytes != 8)
		goto out;

	if (X86_MODRM_MOD(insn->modrm.value) == 3) {
		ret = get_eff_addr_reg(insn, regs, &regoff, &eff_addr);
		if (ret)
			goto out;

	} else {
		if (insn->sib.nbytes) {
			ret = get_eff_addr_sib(insn, regs, &regoff, &eff_addr);
			if (ret)
				goto out;
		} else {
			ret = get_eff_addr_modrm(insn, regs, &regoff, &eff_addr);
			if (ret)
				goto out;
		}

	}

	ret = get_seg_base_limit(insn, regs, regoff, &seg_base, NULL);
	if (ret)
		goto out;

	linear_addr = (unsigned long)eff_addr + seg_base;

out:
	return (void __user *)linear_addr;
}
