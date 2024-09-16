static gro_result_t napi_skb_finish(gro_result_t ret, struct sk_buff *skb)
{
	switch (ret) {
	case GRO_NORMAL:
		if (netif_receive_skb_internal(skb))
			ret = GRO_DROP;
		break;

	case GRO_DROP:
		kfree_skb(skb);
		break;

	case GRO_MERGED_FREE:
		if (NAPI_GRO_CB(skb)->free == NAPI_GRO_FREE_STOLEN_HEAD) {
			skb_dst_drop(skb);
			kmem_cache_free(skbuff_head_cache, skb);
		} else {
			__kfree_skb(skb);
		}
		break;

	case GRO_HELD:
	case GRO_MERGED:
		break;
	}

	return ret;
}
