void CNB::PopulateIPLength(IPv4Header *IpHeader, USHORT IpLength) const
{
    if ((IpHeader->ip_verlen & 0xF0) == 0x40)
    {
        if (!IpHeader->ip_length) {
            IpHeader->ip_length = swap_short(IpLength);
        }
    }
}
