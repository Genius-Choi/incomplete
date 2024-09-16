void qeth_qdio_start_poll(struct ccw_device *ccwdev, int queue,
		unsigned long card_ptr)
{
	struct qeth_card *card = (struct qeth_card *)card_ptr;

	if (card->dev && (card->dev->flags & IFF_UP))
		napi_schedule(&card->napi);
}
