static struct bt_wait_state *bt_wake_ptr(struct blk_mq_bitmap_tags *bt)
{
	int i, wake_index;

	wake_index = atomic_read(&bt->wake_index);
	for (i = 0; i < BT_WAIT_QUEUES; i++) {
		struct bt_wait_state *bs = &bt->bs[wake_index];

		if (waitqueue_active(&bs->wait)) {
			int o = atomic_read(&bt->wake_index);
			if (wake_index != o)
				atomic_cmpxchg(&bt->wake_index, o, wake_index);

			return bs;
		}

		wake_index = bt_index_inc(wake_index);
	}

	return NULL;
}
