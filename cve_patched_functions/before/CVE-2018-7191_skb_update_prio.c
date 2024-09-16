static void skb_update_prio(struct sk_buff *skb)
{
	struct netprio_map *map = rcu_dereference_bh(skb->dev->priomap);

	if (!skb->priority && skb->sk && map) {
		unsigned int prioidx =
			sock_cgroup_prioidx(&skb->sk->sk_cgrp_data);

		if (prioidx < map->priomap_len)
			skb->priority = map->priomap[prioidx];
	}
}
