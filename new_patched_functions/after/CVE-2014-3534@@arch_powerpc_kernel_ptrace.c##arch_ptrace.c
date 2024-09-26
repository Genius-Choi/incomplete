long arch_ptrace(struct task_struct *child, long request,
		 unsigned long addr, unsigned long data)
{
	ptrace_area parea; 
	int copied, ret;

	switch (request) {
	case PTRACE_PEEKUSR:
		/* read the word at location addr in the USER area. */
		return peek_user(child, addr, data);

	case PTRACE_POKEUSR:
		/* write the word at location addr in the USER area */
		return poke_user(child, addr, data);

	case PTRACE_PEEKUSR_AREA:
	case PTRACE_POKEUSR_AREA:
		if (copy_from_user(&parea, (void __force __user *) addr,
							sizeof(parea)))
			return -EFAULT;
		addr = parea.kernel_addr;
		data = parea.process_addr;
		copied = 0;
		while (copied < parea.len) {
			if (request == PTRACE_PEEKUSR_AREA)
				ret = peek_user(child, addr, data);
			else {
				addr_t utmp;
				if (get_user(utmp,
					     (addr_t __force __user *) data))
					return -EFAULT;
				ret = poke_user(child, addr, utmp);
			}
			if (ret)
				return ret;
			addr += sizeof(unsigned long);
			data += sizeof(unsigned long);
			copied += sizeof(unsigned long);
		}
		return 0;
	case PTRACE_GET_LAST_BREAK:
		put_user(task_thread_info(child)->last_break,
			 (unsigned long __user *) data);
		return 0;
	case PTRACE_ENABLE_TE:
		if (!MACHINE_HAS_TE)
			return -EIO;
		child->thread.per_flags &= ~PER_FLAG_NO_TE;
		return 0;
	case PTRACE_DISABLE_TE:
		if (!MACHINE_HAS_TE)
			return -EIO;
		child->thread.per_flags |= PER_FLAG_NO_TE;
		child->thread.per_flags &= ~PER_FLAG_TE_ABORT_RAND;
		return 0;
	case PTRACE_TE_ABORT_RAND:
		if (!MACHINE_HAS_TE || (child->thread.per_flags & PER_FLAG_NO_TE))
			return -EIO;
		switch (data) {
		case 0UL:
			child->thread.per_flags &= ~PER_FLAG_TE_ABORT_RAND;
			break;
		case 1UL:
			child->thread.per_flags |= PER_FLAG_TE_ABORT_RAND;
			child->thread.per_flags |= PER_FLAG_TE_ABORT_RAND_TEND;
			break;
		case 2UL:
			child->thread.per_flags |= PER_FLAG_TE_ABORT_RAND;
			child->thread.per_flags &= ~PER_FLAG_TE_ABORT_RAND_TEND;
			break;
		default:
			return -EINVAL;
		}
		return 0;
	default:
		/* Removing high order bit from addr (only for 31 bit). */
		addr &= PSW_ADDR_INSN;
		return ptrace_request(child, request, addr, data);
	}
}
