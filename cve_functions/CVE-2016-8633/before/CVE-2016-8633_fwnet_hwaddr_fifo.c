static __u64 fwnet_hwaddr_fifo(union fwnet_hwaddr *ha)
{
	return (u64)get_unaligned_be16(&ha->uc.fifo_hi) << 32
	       | get_unaligned_be32(&ha->uc.fifo_lo);
}
