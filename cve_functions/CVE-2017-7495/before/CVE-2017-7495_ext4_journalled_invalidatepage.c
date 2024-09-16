static void ext4_journalled_invalidatepage(struct page *page,
					   unsigned int offset,
					   unsigned int length)
{
	WARN_ON(__ext4_journalled_invalidatepage(page, offset, length) < 0);
}
