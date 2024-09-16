static void fwnet_write_complete(struct fw_card *card, int rcode,
				 void *payload, size_t length, void *data)
{
	struct fwnet_packet_task *ptask = data;
	static unsigned long j;
	static int last_rcode, errors_skipped;

	if (rcode == RCODE_COMPLETE) {
		fwnet_transmit_packet_done(ptask);
	} else {
		if (printk_timed_ratelimit(&j,  1000) || rcode != last_rcode) {
			dev_err(&ptask->dev->netdev->dev,
				"fwnet_write_complete failed: %x (skipped %d)\n",
				rcode, errors_skipped);

			errors_skipped = 0;
			last_rcode = rcode;
		} else {
			errors_skipped++;
		}
		fwnet_transmit_packet_failed(ptask);
	}
}
