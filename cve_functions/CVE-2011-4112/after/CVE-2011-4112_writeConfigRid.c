static int writeConfigRid(struct airo_info *ai, int lock)
{
	ConfigRid cfgr;

	if (!test_bit (FLAG_COMMIT, &ai->flags))
		return SUCCESS;

	clear_bit (FLAG_COMMIT, &ai->flags);
	clear_bit (FLAG_RESET, &ai->flags);
	checkThrottle(ai);
	cfgr = ai->config;

	if ((cfgr.opmode & MODE_CFG_MASK) == MODE_STA_IBSS)
		set_bit(FLAG_ADHOC, &ai->flags);
	else
		clear_bit(FLAG_ADHOC, &ai->flags);

	return PC4500_writerid( ai, RID_CONFIG, &cfgr, sizeof(cfgr), lock);
}
