static struct arm_pmu *__init armv8_pmuv3_pmu_init(void)
{
	armv8pmu.name			= "arm/armv8-pmuv3";
	armv8pmu.map_event		= armv8_pmuv3_map_event;
	armv8pmu.num_events		= armv8pmu_read_num_pmnc_events();
	armv8pmu.set_event_filter	= armv8pmu_set_event_filter;
	return &armv8pmu;
}
