static unsigned long sec_attr_to_key_ref(unsigned int attr)
{
	if (attr == 1 || attr == 2)
		return attr;
	return 0;
}
