int xt_compat_calc_jump(u_int8_t af, unsigned int offset)
{
	struct compat_delta *tmp = xt[af].compat_tab;
	int mid, left = 0, right = xt[af].cur - 1;

	while (left <= right) {
		mid = (left + right) >> 1;
		if (offset > tmp[mid].offset)
			left = mid + 1;
		else if (offset < tmp[mid].offset)
			right = mid - 1;
		else
			return mid ? tmp[mid - 1].delta : 0;
	}
	return left ? tmp[left - 1].delta : 0;
}
