static int tg3_ape_wait_for_event(struct tg3 *tp, u32 timeout_us)
{
	u32 i, apedata;

	for (i = 0; i < timeout_us / 10; i++) {
		apedata = tg3_ape_read32(tp, TG3_APE_EVENT_STATUS);

		if (!(apedata & APE_EVENT_STATUS_EVENT_PENDING))
			break;

		udelay(10);
	}

	return i == timeout_us / 10;
}
