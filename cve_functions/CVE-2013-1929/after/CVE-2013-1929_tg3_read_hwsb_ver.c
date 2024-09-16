static void tg3_read_hwsb_ver(struct tg3 *tp)
{
	u32 val, major, minor;

	/* Use native endian representation */
	if (tg3_nvram_read(tp, TG3_NVM_HWSB_CFG1, &val))
		return;

	major = (val & TG3_NVM_HWSB_CFG1_MAJMSK) >>
		TG3_NVM_HWSB_CFG1_MAJSFT;
	minor = (val & TG3_NVM_HWSB_CFG1_MINMSK) >>
		TG3_NVM_HWSB_CFG1_MINSFT;

	snprintf(&tp->fw_ver[0], 32, "sb v%d.%02d", major, minor);
}
