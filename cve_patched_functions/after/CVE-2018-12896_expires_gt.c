static inline int expires_gt(u64 expires, u64 new_exp)
{
	return expires == 0 || expires > new_exp;
}
