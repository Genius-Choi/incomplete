fversion(FILE * f)
{
    fprintf(f, "w3m version %s, options %s\n", w3m_version,
#if LANG == JA
	    "lang=ja"
#else
	    "lang=en"
#endif
#ifdef USE_M17N
	    ",m17n"
#endif
#ifdef USE_IMAGE
	    ",image"
#endif
#ifdef USE_COLOR
	    ",color"
#ifdef USE_ANSI_COLOR
	    ",ansi-color"
#endif
#endif
#ifdef USE_MOUSE
	    ",mouse"
#ifdef USE_GPM
	    ",gpm"
#endif
#ifdef USE_SYSMOUSE
	    ",sysmouse"
#endif
#endif
#ifdef USE_MENU
	    ",menu"
#endif
#ifdef USE_COOKIE
	    ",cookie"
#endif
#ifdef USE_SSL
	    ",ssl"
#ifdef USE_SSL_VERIFY
	    ",ssl-verify"
#endif
#endif
#ifdef USE_EXTERNAL_URI_LOADER
	    ",external-uri-loader"
#endif
#ifdef USE_W3MMAILER
	    ",w3mmailer"
#endif
#ifdef USE_NNTP
	    ",nntp"
#endif
#ifdef USE_GOPHER
	    ",gopher"
#endif
#ifdef INET6
	    ",ipv6"
#endif
#ifdef USE_ALARM
	    ",alarm"
#endif
#ifdef USE_MARK
	    ",mark"
#endif
#ifdef USE_MIGEMO
	    ",migemo"
#endif
	);
}
