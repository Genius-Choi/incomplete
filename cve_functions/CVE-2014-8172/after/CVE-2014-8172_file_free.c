static inline void file_free(struct file *f)
{
	percpu_counter_dec(&nr_files);
	file_check_state(f);
	call_rcu(&f->f_u.fu_rcuhead, file_free_rcu);
}
