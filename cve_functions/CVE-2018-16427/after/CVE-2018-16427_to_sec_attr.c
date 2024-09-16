static unsigned int to_sec_attr(unsigned int method, unsigned int key_ref)
{
	if (method == SC_AC_NEVER || method == SC_AC_NONE)
		return method;
	if (method == SC_AC_CHV  &&  (key_ref == 1 || key_ref == 2))
		return key_ref;
	return 0;
}
