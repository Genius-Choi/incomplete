static u32 desc_limit_scaled(struct desc_struct *desc)
{
	u32 limit = get_desc_limit(desc);

	return desc->g ? (limit << 12) | 0xfff : limit;
}
