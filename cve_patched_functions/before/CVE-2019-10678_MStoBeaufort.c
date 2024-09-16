int MStoBeaufort(const float ms)
{
	if (ms < 0.3f)
		return 0;
	if (ms < 1.5f)
		return 1;
	if (ms < 3.3f)
		return 2;
	if (ms < 5.5f)
		return 3;
	if (ms < 8.0f)
		return 4;
	if (ms < 10.8f)
		return 5;
	if (ms < 13.9f)
		return 6;
	if (ms < 17.2f)
		return 7;
	if (ms < 20.7f)
		return 8;
	if (ms < 24.5f)
		return 9;
	if (ms < 28.4f)
		return 10;
	if (ms < 32.6f)
		return 11;
	return 12;
}
