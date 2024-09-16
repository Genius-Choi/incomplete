static void f_midi_free_inst(struct usb_function_instance *f)
{
	struct f_midi_opts *opts;

	opts = container_of(f, struct f_midi_opts, func_inst);

	if (opts->id_allocated)
		kfree(opts->id);

	kfree(opts);
}
