struct sock *dn_sklist_find_listener(struct sockaddr_dn *addr)
{
	struct hlist_head *list = listen_hash(addr);
	struct sock *sk;

	read_lock(&dn_hash_lock);
	sk_for_each(sk, list) {
		struct dn_scp *scp = DN_SK(sk);
		if (sk->sk_state != TCP_LISTEN)
			continue;
		if (scp->addr.sdn_objnum) {
			if (scp->addr.sdn_objnum != addr->sdn_objnum)
				continue;
		} else {
			if (addr->sdn_objnum)
				continue;
			if (scp->addr.sdn_objnamel != addr->sdn_objnamel)
				continue;
			if (memcmp(scp->addr.sdn_objname, addr->sdn_objname, le16_to_cpu(addr->sdn_objnamel)) != 0)
				continue;
		}
		sock_hold(sk);
		read_unlock(&dn_hash_lock);
		return sk;
	}

	sk = sk_head(&dn_wild_sk);
	if (sk) {
		if (sk->sk_state == TCP_LISTEN)
			sock_hold(sk);
		else
			sk = NULL;
	}

	read_unlock(&dn_hash_lock);
	return sk;
}
