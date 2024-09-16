static __maybe_unused void i2c_reloc(void)
{
	static int relocated;

	if (!relocated) {
		fixup_cmdtable(cmd_i2c_sub, ARRAY_SIZE(cmd_i2c_sub));
		relocated = 1;
	};
}
