static inline u32 tg3_rx_ret_ring_size(struct tg3 *tp)
{
	if (tg3_flag(tp, LRG_PROD_RING_CAP))
		return TG3_RX_RET_MAX_SIZE_5717;
	else if (tg3_flag(tp, JUMBO_CAPABLE) && !tg3_flag(tp, 5780_CLASS))
		return TG3_RX_RET_MAX_SIZE_5700;
	else
		return TG3_RX_RET_MAX_SIZE_5705;
}
