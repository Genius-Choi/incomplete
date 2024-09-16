static int ip6mr_rtm_dumproute(struct sk_buff *skb, struct netlink_callback *cb)
{
	struct net *net = sock_net(skb->sk);
	struct mr6_table *mrt;
	struct mfc6_cache *mfc;
	unsigned int t = 0, s_t;
	unsigned int h = 0, s_h;
	unsigned int e = 0, s_e;

	s_t = cb->args[0];
	s_h = cb->args[1];
	s_e = cb->args[2];

	read_lock(&mrt_lock);
	ip6mr_for_each_table(mrt, net) {
		if (t < s_t)
			goto next_table;
		if (t > s_t)
			s_h = 0;
		for (h = s_h; h < MFC6_LINES; h++) {
			list_for_each_entry(mfc, &mrt->mfc6_cache_array[h], list) {
				if (e < s_e)
					goto next_entry;
				if (ip6mr_fill_mroute(mrt, skb,
						      NETLINK_CB(cb->skb).portid,
						      cb->nlh->nlmsg_seq,
						      mfc, RTM_NEWROUTE,
						      NLM_F_MULTI) < 0)
					goto done;
next_entry:
				e++;
			}
			e = s_e = 0;
		}
		spin_lock_bh(&mfc_unres_lock);
		list_for_each_entry(mfc, &mrt->mfc6_unres_queue, list) {
			if (e < s_e)
				goto next_entry2;
			if (ip6mr_fill_mroute(mrt, skb,
					      NETLINK_CB(cb->skb).portid,
					      cb->nlh->nlmsg_seq,
					      mfc, RTM_NEWROUTE,
					      NLM_F_MULTI) < 0) {
				spin_unlock_bh(&mfc_unres_lock);
				goto done;
			}
next_entry2:
			e++;
		}
		spin_unlock_bh(&mfc_unres_lock);
		e = s_e = 0;
		s_h = 0;
next_table:
		t++;
	}
done:
	read_unlock(&mrt_lock);

	cb->args[2] = e;
	cb->args[1] = h;
	cb->args[0] = t;

	return skb->len;
}
