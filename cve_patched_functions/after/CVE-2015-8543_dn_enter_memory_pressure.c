static void dn_enter_memory_pressure(struct sock *sk)
{
	if (!dn_memory_pressure) {
		dn_memory_pressure = 1;
	}
}
