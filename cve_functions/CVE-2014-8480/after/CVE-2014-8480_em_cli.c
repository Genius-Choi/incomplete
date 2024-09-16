static int em_cli(struct x86_emulate_ctxt *ctxt)
{
	if (emulator_bad_iopl(ctxt))
		return emulate_gp(ctxt, 0);

	ctxt->eflags &= ~X86_EFLAGS_IF;
	return X86EMUL_CONTINUE;
}
