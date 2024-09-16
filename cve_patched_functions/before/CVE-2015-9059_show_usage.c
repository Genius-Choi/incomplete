show_usage(char *name)
{
	char *s;

	s = strrchr(name, '/');
	s = s ? s+1 : name;

	printf("picocom v%s\n", VERSION_STR);

	printf("\nCompiled-in options:\n");
	printf("  TTY_Q_SZ is %d\n", TTY_Q_SZ);
#ifdef USE_HIGH_BAUD
	printf("  HIGH_BAUD is enabled\n");
#endif
#ifdef USE_FLOCK
	printf("  USE_FLOCK is enabled\n");
#endif
#ifdef UUCP_LOCK_DIR
	printf("  UUCP_LOCK_DIR is: %s\n", UUCP_LOCK_DIR);
#endif
#ifdef LINENOISE
	printf("  LINENOISE is enabled\n");
	printf("  SEND_RECEIVE_HISTFILE is: %s\n", SEND_RECEIVE_HISTFILE);
#endif
	
	printf("\nUsage is: %s [options] <tty device>\n", s);
	printf("Options are:\n");
	printf("  --<b>aud <baudrate>\n");
	printf("  --<f>low s (=soft) | h (=hard) | n (=none)\n");
	printf("  --<p>arity o (=odd) | e (=even) | n (=none)\n");
	printf("  --<d>atabits 5 | 6 | 7 | 8\n");
	printf("  --<e>scape <char>\n");
	printf("  --e<c>ho\n");
	printf("  --no<i>nit\n");
	printf("  --no<r>eset\n");
	printf("  --no<l>ock\n");
	printf("  --<s>end-cmd <command>\n");
	printf("  --recei<v>e-cmd <command>\n");
	printf("  --imap <map> (input mappings)\n");
	printf("  --omap <map> (output mappings)\n");
	printf("  --emap <map> (local-echo mappings)\n");
	printf("  --<h>elp\n");
	printf("<map> is a comma-separated list of one or more of:\n");
	printf("  crlf : map CR --> LF\n");
	printf("  crcrlf : map CR --> CR + LF\n");
	printf("  igncr : ignore CR\n");
	printf("  lfcr : map LF --> CR\n");
	printf("  lfcrlf : map LF --> CR + LF\n");
	printf("  ignlf : ignore LF\n");
	printf("  bsdel : map BS --> DEL\n");
	printf("  delbs : map DEL --> BS\n");
	printf("<?> indicates the equivalent short option.\n");
	printf("Short options are prefixed by \"-\" instead of by \"--\".\n");
}
