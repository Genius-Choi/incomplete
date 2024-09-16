static void __net_exit ip6_tnl_destroy_tunnels(struct ip6_tnl_net *ip6n)
{
	int h;
	struct ip6_tnl *t;
	LIST_HEAD(list);

	for (h = 0; h < HASH_SIZE; h++) {
		t = ip6n->tnls_r_l[h];
		while (t != NULL) {
			unregister_netdevice_queue(t->dev, &list);
			t = t->next;
		}
	}

	t = ip6n->tnls_wc[0];
	unregister_netdevice_queue(t->dev, &list);
	unregister_netdevice_many(&list);
}
