xfs_wait_buftarg(
	struct xfs_buftarg	*btp)
{
	struct xfs_buf		*bp;

restart:
	spin_lock(&btp->bt_lru_lock);
	while (!list_empty(&btp->bt_lru)) {
		bp = list_first_entry(&btp->bt_lru, struct xfs_buf, b_lru);
		if (atomic_read(&bp->b_hold) > 1) {
			spin_unlock(&btp->bt_lru_lock);
			delay(100);
			goto restart;
		}
		/*
		 * clear the LRU reference count so the buffer doesn't get
		 * ignored in xfs_buf_rele().
		 */
		atomic_set(&bp->b_lru_ref, 0);
		spin_unlock(&btp->bt_lru_lock);
		xfs_buf_rele(bp);
		spin_lock(&btp->bt_lru_lock);
	}
	spin_unlock(&btp->bt_lru_lock);
}
