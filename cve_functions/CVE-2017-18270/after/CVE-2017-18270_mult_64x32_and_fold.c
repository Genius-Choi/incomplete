static u64 mult_64x32_and_fold(u64 x, u32 y)
{
	u64 hi = (u64)(u32)(x >> 32) * y;
	u64 lo = (u64)(u32)(x) * y;
	return lo + ((u64)(u32)hi << 32) + (u32)(hi >> 32);
}
