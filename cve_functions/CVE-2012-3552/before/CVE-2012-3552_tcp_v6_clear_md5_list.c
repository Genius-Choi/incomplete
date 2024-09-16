static void tcp_v6_clear_md5_list (struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);
	int i;

	if (tp->md5sig_info->entries6) {
		for (i = 0; i < tp->md5sig_info->entries6; i++)
			kfree(tp->md5sig_info->keys6[i].base.key);
		tp->md5sig_info->entries6 = 0;
		tcp_free_md5sig_pool();
	}

	kfree(tp->md5sig_info->keys6);
	tp->md5sig_info->keys6 = NULL;
	tp->md5sig_info->alloced6 = 0;

	if (tp->md5sig_info->entries4) {
		for (i = 0; i < tp->md5sig_info->entries4; i++)
			kfree(tp->md5sig_info->keys4[i].base.key);
		tp->md5sig_info->entries4 = 0;
		tcp_free_md5sig_pool();
	}

	kfree(tp->md5sig_info->keys4);
	tp->md5sig_info->keys4 = NULL;
	tp->md5sig_info->alloced4 = 0;
}
