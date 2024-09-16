static int hugetlbfs_migrate_page(struct address_space *mapping,
				struct page *newpage, struct page *page,
				enum migrate_mode mode)
{
	int rc;

	rc = migrate_huge_page_move_mapping(mapping, newpage, page);
	if (rc)
		return rc;
	migrate_page_copy(newpage, page);

	return 0;
}
