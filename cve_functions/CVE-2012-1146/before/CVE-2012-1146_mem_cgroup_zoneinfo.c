mem_cgroup_zoneinfo(struct mem_cgroup *memcg, int nid, int zid)
{
	return &memcg->info.nodeinfo[nid]->zoneinfo[zid];
}
