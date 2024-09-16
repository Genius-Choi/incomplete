struct sk_buff *__skb_gso_segment(struct sk_buff *skb,
				  netdev_features_t features, bool tx_path)
{
	if (unlikely(skb_needs_check(skb, tx_path))) {
		int err;

		skb_warn_bad_offload(skb);

		err = skb_cow_head(skb, 0);
		if (err < 0)
			return ERR_PTR(err);
	}

	BUILD_BUG_ON(SKB_SGO_CB_OFFSET +
		     sizeof(*SKB_GSO_CB(skb)) > sizeof(skb->cb));

	SKB_GSO_CB(skb)->mac_offset = skb_headroom(skb);
	SKB_GSO_CB(skb)->encap_level = 0;

	skb_reset_mac_header(skb);
	skb_reset_mac_len(skb);

	return skb_mac_gso_segment(skb, features);
}
