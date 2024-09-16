void bpf_prog_put_rcu(struct bpf_prog *prog)
{
	if (atomic_dec_and_test(&prog->aux->refcnt))
		call_rcu(&prog->aux->rcu, __prog_put_common);
}
