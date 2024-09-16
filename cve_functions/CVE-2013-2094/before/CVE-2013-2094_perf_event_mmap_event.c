static void perf_event_mmap_event(struct perf_mmap_event *mmap_event)
{
	struct perf_cpu_context *cpuctx;
	struct perf_event_context *ctx;
	struct vm_area_struct *vma = mmap_event->vma;
	struct file *file = vma->vm_file;
	unsigned int size;
	char tmp[16];
	char *buf = NULL;
	const char *name;
	struct pmu *pmu;
	int ctxn;

	memset(tmp, 0, sizeof(tmp));

	if (file) {
		/*
		 * d_path works from the end of the rb backwards, so we
		 * need to add enough zero bytes after the string to handle
		 * the 64bit alignment we do later.
		 */
		buf = kzalloc(PATH_MAX + sizeof(u64), GFP_KERNEL);
		if (!buf) {
			name = strncpy(tmp, "//enomem", sizeof(tmp));
			goto got_name;
		}
		name = d_path(&file->f_path, buf, PATH_MAX);
		if (IS_ERR(name)) {
			name = strncpy(tmp, "//toolong", sizeof(tmp));
			goto got_name;
		}
	} else {
		if (arch_vma_name(mmap_event->vma)) {
			name = strncpy(tmp, arch_vma_name(mmap_event->vma),
				       sizeof(tmp) - 1);
			tmp[sizeof(tmp) - 1] = '\0';
			goto got_name;
		}

		if (!vma->vm_mm) {
			name = strncpy(tmp, "[vdso]", sizeof(tmp));
			goto got_name;
		} else if (vma->vm_start <= vma->vm_mm->start_brk &&
				vma->vm_end >= vma->vm_mm->brk) {
			name = strncpy(tmp, "[heap]", sizeof(tmp));
			goto got_name;
		} else if (vma->vm_start <= vma->vm_mm->start_stack &&
				vma->vm_end >= vma->vm_mm->start_stack) {
			name = strncpy(tmp, "[stack]", sizeof(tmp));
			goto got_name;
		}

		name = strncpy(tmp, "//anon", sizeof(tmp));
		goto got_name;
	}

got_name:
	size = ALIGN(strlen(name)+1, sizeof(u64));

	mmap_event->file_name = name;
	mmap_event->file_size = size;

	mmap_event->event_id.header.size = sizeof(mmap_event->event_id) + size;

	rcu_read_lock();
	list_for_each_entry_rcu(pmu, &pmus, entry) {
		cpuctx = get_cpu_ptr(pmu->pmu_cpu_context);
		if (cpuctx->unique_pmu != pmu)
			goto next;
		perf_event_mmap_ctx(&cpuctx->ctx, mmap_event,
					vma->vm_flags & VM_EXEC);

		ctxn = pmu->task_ctx_nr;
		if (ctxn < 0)
			goto next;

		ctx = rcu_dereference(current->perf_event_ctxp[ctxn]);
		if (ctx) {
			perf_event_mmap_ctx(ctx, mmap_event,
					vma->vm_flags & VM_EXEC);
		}
next:
		put_cpu_ptr(pmu->pmu_cpu_context);
	}
	rcu_read_unlock();

	kfree(buf);
}
