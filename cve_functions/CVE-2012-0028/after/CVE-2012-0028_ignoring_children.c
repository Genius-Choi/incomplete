static int ignoring_children(struct task_struct *parent)
{
	int ret;
	struct sighand_struct *psig = parent->sighand;
	unsigned long flags;
	spin_lock_irqsave(&psig->siglock, flags);
	ret = (psig->action[SIGCHLD-1].sa.sa_handler == SIG_IGN ||
	       (psig->action[SIGCHLD-1].sa.sa_flags & SA_NOCLDWAIT));
	spin_unlock_irqrestore(&psig->siglock, flags);
	return ret;
}
