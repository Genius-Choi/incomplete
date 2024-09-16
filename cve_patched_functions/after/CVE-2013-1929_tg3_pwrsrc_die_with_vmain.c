static void tg3_pwrsrc_die_with_vmain(struct tg3 *tp)
{
	u32 grc_local_ctrl;

	if (!tg3_flag(tp, IS_NIC) ||
	    tg3_asic_rev(tp) == ASIC_REV_5700 ||
	    tg3_asic_rev(tp) == ASIC_REV_5701)
		return;

	grc_local_ctrl = tp->grc_local_ctrl | GRC_LCLCTRL_GPIO_OE1;

	tw32_wait_f(GRC_LOCAL_CTRL,
		    grc_local_ctrl | GRC_LCLCTRL_GPIO_OUTPUT1,
		    TG3_GRC_LCLCTL_PWRSW_DELAY);

	tw32_wait_f(GRC_LOCAL_CTRL,
		    grc_local_ctrl,
		    TG3_GRC_LCLCTL_PWRSW_DELAY);

	tw32_wait_f(GRC_LOCAL_CTRL,
		    grc_local_ctrl | GRC_LCLCTRL_GPIO_OUTPUT1,
		    TG3_GRC_LCLCTL_PWRSW_DELAY);
}
