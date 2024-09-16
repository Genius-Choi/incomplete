static bool move_anon(void)
{
	return test_bit(MOVE_CHARGE_TYPE_ANON,
					&mc.to->move_charge_at_immigrate);
}
