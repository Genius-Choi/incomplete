static int readCapabilityRid(struct airo_info *ai, CapabilityRid *capr, int lock)
{
	return PC4500_readrid(ai, RID_CAPABILITIES, capr, sizeof(*capr), lock);
}
