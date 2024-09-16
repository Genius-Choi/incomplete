asmlinkage void __exception do_undefinstr(struct pt_regs *regs)
{
	unsigned int instr;
	siginfo_t info;
	void __user *pc;

	pc = (void __user *)instruction_pointer(regs);

	if (processor_mode(regs) == SVC_MODE) {
#ifdef CONFIG_THUMB2_KERNEL
		if (thumb_mode(regs)) {
			instr = ((u16 *)pc)[0];
			if (is_wide_instruction(instr)) {
				instr <<= 16;
				instr |= ((u16 *)pc)[1];
			}
		} else
#endif
			instr = *(u32 *) pc;
	} else if (thumb_mode(regs)) {
		if (get_user(instr, (u16 __user *)pc))
			goto die_sig;
		if (is_wide_instruction(instr)) {
			unsigned int instr2;
			if (get_user(instr2, (u16 __user *)pc+1))
				goto die_sig;
			instr <<= 16;
			instr |= instr2;
		}
	} else if (get_user(instr, (u32 __user *)pc)) {
		goto die_sig;
	}

	if (call_undef_hook(regs, instr) == 0)
		return;

die_sig:
#ifdef CONFIG_DEBUG_USER
	if (user_debug & UDBG_UNDEFINED) {
		printk(KERN_INFO "%s (%d): undefined instruction: pc=%p\n",
			current->comm, task_pid_nr(current), pc);
		dump_instr(KERN_INFO, regs);
	}
#endif

	info.si_signo = SIGILL;
	info.si_errno = 0;
	info.si_code  = ILL_ILLOPC;
	info.si_addr  = pc;

	arm_notify_die("Oops - undefined instruction", regs, &info, 0, 6);
}
