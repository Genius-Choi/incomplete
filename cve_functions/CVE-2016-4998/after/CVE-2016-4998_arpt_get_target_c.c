arpt_get_target_c(const struct arpt_entry *e)
{
	return arpt_get_target((struct arpt_entry *)e);
}
