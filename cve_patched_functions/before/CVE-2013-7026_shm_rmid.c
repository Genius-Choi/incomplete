static inline void shm_rmid(struct ipc_namespace *ns, struct shmid_kernel *s)
{
	ipc_rmid(&shm_ids(ns), &s->shm_perm);
}
