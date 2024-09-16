static void release_tgcred_rcu(struct rcu_head *rcu)
{
	struct thread_group_cred *tgcred =
		container_of(rcu, struct thread_group_cred, rcu);

	BUG_ON(atomic_read(&tgcred->usage) != 0);

	key_put(tgcred->session_keyring);
	key_put(tgcred->process_keyring);
	kfree(tgcred);
}
