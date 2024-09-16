do_general_protection(struct pt_regs *regs, long error_code)
{
	struct task_struct *tsk;
	enum ctx_state prev_state;

	prev_state = exception_enter();
	conditional_sti(regs);

#ifdef CONFIG_X86_32
	if (regs->flags & X86_VM_MASK) {
		local_irq_enable();
		handle_vm86_fault((struct kernel_vm86_regs *) regs, error_code);
		goto exit;
	}
#endif

	tsk = current;
	if (!user_mode(regs)) {
		if (fixup_exception(regs))
			goto exit;

		tsk->thread.error_code = error_code;
		tsk->thread.trap_nr = X86_TRAP_GP;
		if (notify_die(DIE_GPF, "general protection fault", regs, error_code,
			       X86_TRAP_GP, SIGSEGV) != NOTIFY_STOP)
			die("general protection fault", regs, error_code);
		goto exit;
	}

	tsk->thread.error_code = error_code;
	tsk->thread.trap_nr = X86_TRAP_GP;

	if (show_unhandled_signals && unhandled_signal(tsk, SIGSEGV) &&
			printk_ratelimit()) {
		pr_info("%s[%d] general protection ip:%lx sp:%lx error:%lx",
			tsk->comm, task_pid_nr(tsk),
			regs->ip, regs->sp, error_code);
		print_vma_addr(" in ", regs->ip);
		pr_cont("\n");
	}

	force_sig_info(SIGSEGV, SEND_SIG_PRIV, tsk);
exit:
	exception_exit(prev_state);
}
