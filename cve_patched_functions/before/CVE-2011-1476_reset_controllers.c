static void reset_controllers(int dev, unsigned char *controller, int update_dev)
{
	int i;
	for (i = 0; i < 128; i++)
		controller[i] = ctrl_def_values[i];
}
