last_byte_offset(u64 start, u64 len)
{
	u64 end;

	WARN_ON_ONCE(!len);
	end = start + len;
	return end > start ? end - 1: NFS4_MAX_UINT64;
}
