uint32_t SystemUptime()
{
#if defined(WIN32)
	return static_cast<uint32_t>(GetTickCount64() / 1000u);
#elif defined(__linux__) || defined(__linux) || defined(linux)
	struct sysinfo info;
	if (sysinfo(&info) != 0)
		return -1;
	return info.uptime;
#elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
	struct timeval boottime;
	std::size_t len = sizeof(boottime);
	int mib[2] = { CTL_KERN, KERN_BOOTTIME };
	if (sysctl(mib, 2, &boottime, &len, NULL, 0) < 0)
		return -1;
	return time(NULL) - boottime.tv_sec;
#elif (defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__)) && defined(CLOCK_UPTIME)
	struct timespec ts;
	if (clock_gettime(CLOCK_UPTIME, &ts) != 0)
		return -1;
	return ts.tv_sec;
#else
	return 0;
#endif
}
