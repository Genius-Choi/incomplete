int btrfs_truncate_page(struct inode *inode, loff_t from, loff_t len,
			int front)
{
	struct address_space *mapping = inode->i_mapping;
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct extent_io_tree *io_tree = &BTRFS_I(inode)->io_tree;
	struct btrfs_ordered_extent *ordered;
	struct extent_state *cached_state = NULL;
	char *kaddr;
	u32 blocksize = root->sectorsize;
	pgoff_t index = from >> PAGE_CACHE_SHIFT;
	unsigned offset = from & (PAGE_CACHE_SIZE-1);
	struct page *page;
	gfp_t mask = btrfs_alloc_write_mask(mapping);
	int ret = 0;
	u64 page_start;
	u64 page_end;

	if ((offset & (blocksize - 1)) == 0 &&
	    (!len || ((len & (blocksize - 1)) == 0)))
		goto out;
	ret = btrfs_delalloc_reserve_space(inode, PAGE_CACHE_SIZE);
	if (ret)
		goto out;

again:
	page = find_or_create_page(mapping, index, mask);
	if (!page) {
		btrfs_delalloc_release_space(inode, PAGE_CACHE_SIZE);
		ret = -ENOMEM;
		goto out;
	}

	page_start = page_offset(page);
	page_end = page_start + PAGE_CACHE_SIZE - 1;

	if (!PageUptodate(page)) {
		ret = btrfs_readpage(NULL, page);
		lock_page(page);
		if (page->mapping != mapping) {
			unlock_page(page);
			page_cache_release(page);
			goto again;
		}
		if (!PageUptodate(page)) {
			ret = -EIO;
			goto out_unlock;
		}
	}
	wait_on_page_writeback(page);

	lock_extent_bits(io_tree, page_start, page_end, 0, &cached_state);
	set_page_extent_mapped(page);

	ordered = btrfs_lookup_ordered_extent(inode, page_start);
	if (ordered) {
		unlock_extent_cached(io_tree, page_start, page_end,
				     &cached_state, GFP_NOFS);
		unlock_page(page);
		page_cache_release(page);
		btrfs_start_ordered_extent(inode, ordered, 1);
		btrfs_put_ordered_extent(ordered);
		goto again;
	}

	clear_extent_bit(&BTRFS_I(inode)->io_tree, page_start, page_end,
			  EXTENT_DIRTY | EXTENT_DELALLOC |
			  EXTENT_DO_ACCOUNTING | EXTENT_DEFRAG,
			  0, 0, &cached_state, GFP_NOFS);

	ret = btrfs_set_extent_delalloc(inode, page_start, page_end,
					&cached_state);
	if (ret) {
		unlock_extent_cached(io_tree, page_start, page_end,
				     &cached_state, GFP_NOFS);
		goto out_unlock;
	}

	if (offset != PAGE_CACHE_SIZE) {
		if (!len)
			len = PAGE_CACHE_SIZE - offset;
		kaddr = kmap(page);
		if (front)
			memset(kaddr, 0, offset);
		else
			memset(kaddr + offset, 0, len);
		flush_dcache_page(page);
		kunmap(page);
	}
	ClearPageChecked(page);
	set_page_dirty(page);
	unlock_extent_cached(io_tree, page_start, page_end, &cached_state,
			     GFP_NOFS);

out_unlock:
	if (ret)
		btrfs_delalloc_release_space(inode, PAGE_CACHE_SIZE);
	unlock_page(page);
	page_cache_release(page);
out:
	return ret;
}
