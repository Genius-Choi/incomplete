static inline void setup_pegasus_II(pegasus_t *pegasus)
{
	__u8 data = 0xa5;

	set_register(pegasus, Reg1d, 0);
	set_register(pegasus, Reg7b, 1);
	mdelay(100);
	if ((pegasus->features & HAS_HOME_PNA) && mii_mode)
		set_register(pegasus, Reg7b, 0);
	else
		set_register(pegasus, Reg7b, 2);

	set_register(pegasus, 0x83, data);
	get_registers(pegasus, 0x83, 1, &data);

	if (data == 0xa5)
		pegasus->chip = 0x8513;
	else
		pegasus->chip = 0;

	set_register(pegasus, 0x80, 0xc0);
	set_register(pegasus, 0x83, 0xff);
	set_register(pegasus, 0x84, 0x01);

	if (pegasus->features & HAS_HOME_PNA && mii_mode)
		set_register(pegasus, Reg81, 6);
	else
		set_register(pegasus, Reg81, 2);
}
