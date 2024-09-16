static void attr_vfree(void *attr)
{
	XFREE(MTYPE_ATTR, attr);
}
