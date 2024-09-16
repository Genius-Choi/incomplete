static void bpf_prog_uncharge_memlock(struct bpf_prog *prog)
{
	struct user_struct *user = prog->aux->user;

	atomic_long_sub(prog->pages, &user->locked_vm);
	free_uid(user);
}
