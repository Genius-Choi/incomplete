static unsigned int vfat_striptail_len(const struct qstr *qstr)
{
	return __vfat_striptail_len(qstr->len, qstr->name);
}
