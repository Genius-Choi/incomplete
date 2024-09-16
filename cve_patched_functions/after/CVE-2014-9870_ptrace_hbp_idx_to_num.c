static long ptrace_hbp_idx_to_num(int idx)
{
	long mid = ARM_MAX_BRP << 1;
	long num = (idx << 1) + 1;
	return num > mid ? mid - num : num;
}
