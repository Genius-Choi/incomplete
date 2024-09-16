void remove_conflicting_framebuffers(struct apertures_struct *a,
				     const char *name, bool primary)
{
	mutex_lock(&registration_lock);
	do_remove_conflicting_framebuffers(a, name, primary);
	mutex_unlock(&registration_lock);
}
