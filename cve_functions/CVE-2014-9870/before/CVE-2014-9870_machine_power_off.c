void machine_power_off(void)
{
	machine_shutdown();
	if (pm_power_off)
		pm_power_off();
}
