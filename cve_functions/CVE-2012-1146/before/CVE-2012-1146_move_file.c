static bool move_file(void)
{
	return test_bit(MOVE_CHARGE_TYPE_FILE,
					&mc.to->move_charge_at_immigrate);
}
