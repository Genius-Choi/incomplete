void dousers(void) {
	struct passwd *pw;
	struct group *gr;
	gchar* str;
	if(rungroup) {
		gr=getgrnam(rungroup);
		if(!gr) {
			str = g_strdup_printf("Invalid group name: %s", rungroup);
			err(str);
		}
		if(setgid(gr->gr_gid)<0) {
			err("Could not set GID: %m"); 
		}
	}
	if(runuser) {
		pw=getpwnam(runuser);
		if(!pw) {
			str = g_strdup_printf("Invalid user name: %s", runuser);
			err(str);
		}
		if(setuid(pw->pw_uid)<0) {
			err("Could not set UID: %m");
		}
	}
}
