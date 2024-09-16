static void tg3_recycle_rx(struct tg3_napi *tnapi,
			   struct tg3_rx_prodring_set *dpr,
			   u32 opaque_key, int src_idx,
			   u32 dest_idx_unmasked)
{
	struct tg3 *tp = tnapi->tp;
	struct tg3_rx_buffer_desc *src_desc, *dest_desc;
	struct ring_info *src_map, *dest_map;
	struct tg3_rx_prodring_set *spr = &tp->napi[0].prodring;
	int dest_idx;

	switch (opaque_key) {
	case RXD_OPAQUE_RING_STD:
		dest_idx = dest_idx_unmasked & tp->rx_std_ring_mask;
		dest_desc = &dpr->rx_std[dest_idx];
		dest_map = &dpr->rx_std_buffers[dest_idx];
		src_desc = &spr->rx_std[src_idx];
		src_map = &spr->rx_std_buffers[src_idx];
		break;

	case RXD_OPAQUE_RING_JUMBO:
		dest_idx = dest_idx_unmasked & tp->rx_jmb_ring_mask;
		dest_desc = &dpr->rx_jmb[dest_idx].std;
		dest_map = &dpr->rx_jmb_buffers[dest_idx];
		src_desc = &spr->rx_jmb[src_idx].std;
		src_map = &spr->rx_jmb_buffers[src_idx];
		break;

	default:
		return;
	}

	dest_map->data = src_map->data;
	dma_unmap_addr_set(dest_map, mapping,
			   dma_unmap_addr(src_map, mapping));
	dest_desc->addr_hi = src_desc->addr_hi;
	dest_desc->addr_lo = src_desc->addr_lo;

	/* Ensure that the update to the skb happens after the physical
	 * addresses have been transferred to the new BD location.
	 */
	smp_wmb();

	src_map->data = NULL;
}
