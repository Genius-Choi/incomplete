static int sg_get_version(int __user *p)
{
	static const int sg_version_num = 30527;
	return put_user(sg_version_num, p);
}
