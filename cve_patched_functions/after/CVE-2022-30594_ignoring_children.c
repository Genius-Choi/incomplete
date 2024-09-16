static int ignoring_children(struct sighand_struct *sigh)
{
	int ret;
	spin_lock(&sigh->siglock);
	ret = (sigh->action[SIGCHLD-1].sa.sa_handler == SIG_IGN) ||
	      (sigh->action[SIGCHLD-1].sa.sa_flags & SA_NOCLDWAIT);
	spin_unlock(&sigh->siglock);
	return ret;
}
