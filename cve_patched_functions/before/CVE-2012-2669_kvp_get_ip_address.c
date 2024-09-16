kvp_get_ip_address(int family, char *buffer, int length)
{
	struct ifaddrs *ifap;
	struct ifaddrs *curp;
	int ipv4_len = strlen("255.255.255.255") + 1;
	int ipv6_len = strlen("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff")+1;
	int offset = 0;
	const char *str;
	char tmp[50];
	int error = 0;

	/*
	 * On entry into this function, the buffer is capable of holding the
	 * maximum key value (2048 bytes).
	 */

	if (getifaddrs(&ifap)) {
		strcpy(buffer, "getifaddrs failed\n");
		return 1;
	}

	curp = ifap;
	while (curp != NULL) {
		if ((curp->ifa_addr != NULL) &&
		   (curp->ifa_addr->sa_family == family)) {
			if (family == AF_INET) {
				struct sockaddr_in *addr =
				(struct sockaddr_in *) curp->ifa_addr;

				str = inet_ntop(family, &addr->sin_addr,
						tmp, 50);
				if (str == NULL) {
					strcpy(buffer, "inet_ntop failed\n");
					error = 1;
					goto getaddr_done;
				}
				if (offset == 0)
					strcpy(buffer, tmp);
				else
					strcat(buffer, tmp);
				strcat(buffer, ";");

				offset += strlen(str) + 1;
				if ((length - offset) < (ipv4_len + 1))
					goto getaddr_done;

			} else {

			/*
			 * We only support AF_INET and AF_INET6
			 * and the list of addresses is separated by a ";".
			 */
				struct sockaddr_in6 *addr =
				(struct sockaddr_in6 *) curp->ifa_addr;

				str = inet_ntop(family,
					&addr->sin6_addr.s6_addr,
					tmp, 50);
				if (str == NULL) {
					strcpy(buffer, "inet_ntop failed\n");
					error = 1;
					goto getaddr_done;
				}
				if (offset == 0)
					strcpy(buffer, tmp);
				else
					strcat(buffer, tmp);
				strcat(buffer, ";");
				offset += strlen(str) + 1;
				if ((length - offset) < (ipv6_len + 1))
					goto getaddr_done;

			}

		}
		curp = curp->ifa_next;
	}

getaddr_done:
	freeifaddrs(ifap);
	return error;
}
