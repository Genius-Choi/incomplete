static struct sock *dn_socket_get_first(struct seq_file *seq)
{
	struct dn_iter_state *state = seq->private;
	struct sock *n = NULL;

	for(state->bucket = 0;
	    state->bucket < DN_SK_HASH_SIZE;
	    ++state->bucket) {
		n = sk_head(&dn_sk_hash[state->bucket]);
		if (n)
			break;
	}

	return n;
}
