const char *page_follow_link_light(struct dentry *dentry, void **cookie)
{
	struct page *page = NULL;
	char *res = page_getlink(dentry, &page);
	if (!IS_ERR(res))
		*cookie = page;
	return res;
}
