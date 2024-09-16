static void pretty_print_line(const char *device, const char *fs_type,
			      const char *label, const char *mtpt,
			      const char *uuid)
{
	static int device_len = 10, fs_type_len = 7;
	static int label_len = 8, mtpt_len = 14;
	static int term_width = -1;
	int len, w;

	if (term_width < 0) {
		term_width = get_terminal_width();
		if (term_width <= 0)
			term_width = 80;
	}
	if (term_width > 80) {
		term_width -= 80;
		w = term_width / 10;
		if (w > 8)
			w = 8;
		term_width -= 2*w;
		label_len += w;
		fs_type_len += w;
		w = term_width/2;
		device_len += w;
		mtpt_len +=w;
	}

	len = pretty_print_word(device, device_len, 0, 1);
	len = pretty_print_word(fs_type, fs_type_len, len, 0);
	len = pretty_print_word(label, label_len, len, 0);
	pretty_print_word(mtpt, mtpt_len, len, 0);

	fputs(uuid, stdout);
	fputc('\n', stdout);
}
