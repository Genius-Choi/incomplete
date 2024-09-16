static struct sock *dn_socket_get_next(struct seq_file *seq,
				       struct sock *n)
{
	struct dn_iter_state *state = seq->private;

	n = sk_next(n);
try_again:
	if (n)
		goto out;
	if (++state->bucket >= DN_SK_HASH_SIZE)
		goto out;
	n = sk_head(&dn_sk_hash[state->bucket]);
	goto try_again;
out:
	return n;
}
