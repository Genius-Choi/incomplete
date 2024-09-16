int create_inode(char *pathname, struct inode *i)
{
	TRACE("create_inode: pathname %s\n", pathname);

	if(created_inode[i->inode_number - 1]) {
		TRACE("create_inode: hard link\n");
		if(force)
			unlink(pathname);

		if(link(created_inode[i->inode_number - 1], pathname) == -1) {
			ERROR("create_inode: failed to create hardlink, "
				"because %s\n", strerror(errno));
			return FALSE;
		}

		return TRUE;
	}

	switch(i->type) {
		case SQUASHFS_FILE_TYPE:
		case SQUASHFS_LREG_TYPE:
			TRACE("create_inode: regular file, file_size %lld, "
				"blocks %d\n", i->data, i->blocks);

			if(write_file(i, pathname))
				file_count ++;
                        else
				FAILED = TRUE;
			break;
		case SQUASHFS_SYMLINK_TYPE:
		case SQUASHFS_LSYMLINK_TYPE:
			TRACE("create_inode: symlink, symlink_size %lld\n",
				i->data);

			if(force)
				unlink(pathname);

			if(symlink(i->symlink, pathname) == -1) {
				ERROR("create_inode: failed to create symlink "
					"%s, because %s\n", pathname,
					strerror(errno));
				FAILED = TRUE;
				break;
			}

			write_xattr(pathname, i->xattr);
	
			if(root_process) {
				if(lchown(pathname, i->uid, i->gid) == -1)
					ERROR("create_inode: failed to change "
						"uid and gids on %s, because "
						"%s\n", pathname,
						strerror(errno));
			}

			sym_count ++;
			break;
 		case SQUASHFS_BLKDEV_TYPE:
	 	case SQUASHFS_CHRDEV_TYPE:
 		case SQUASHFS_LBLKDEV_TYPE:
	 	case SQUASHFS_LCHRDEV_TYPE: {
			int chrdev = 0;
			if ( i->type == SQUASHFS_CHRDEV_TYPE ||
					i->type == SQUASHFS_LCHRDEV_TYPE)
				chrdev = 1;

			TRACE("create_inode: dev, rdev 0x%llx\n", i->data);

			if(root_process) {
				if(force)
					unlink(pathname);

				if(mknod(pathname, chrdev ? S_IFCHR : S_IFBLK,
						makedev((i->data >> 8) & 0xff,
						i->data & 0xff)) == -1) {
					ERROR("create_inode: failed to create "
						"%s device %s, because %s\n",
						chrdev ? "character" : "block",
						pathname, strerror(errno));
					FAILED = TRUE;
					break;
				}
				set_attributes(pathname, i->mode, i->uid,
					i->gid, i->time, i->xattr, TRUE);
				dev_count ++;
			} else
				ERROR("create_inode: could not create %s "
					"device %s, because you're not "
					"superuser!\n", chrdev ? "character" :
					"block", pathname);
			break;
		}
		case SQUASHFS_FIFO_TYPE:
		case SQUASHFS_LFIFO_TYPE:
			TRACE("create_inode: fifo\n");

			if(force)
				unlink(pathname);

			if(mknod(pathname, S_IFIFO, 0) == -1) {
				ERROR("create_inode: failed to create fifo %s, "
					"because %s\n", pathname,
					strerror(errno));
				FAILED = TRUE;
				break;
			}
			set_attributes(pathname, i->mode, i->uid, i->gid,
				i->time, i->xattr, TRUE);
			fifo_count ++;
			break;
		case SQUASHFS_SOCKET_TYPE:
		case SQUASHFS_LSOCKET_TYPE:
			TRACE("create_inode: socket\n");
			ERROR("create_inode: socket %s ignored\n", pathname);
			break;
		default:
			ERROR("Unknown inode type %d in create_inode_table!\n",
				i->type);
			return FALSE;
	}

	created_inode[i->inode_number - 1] = strdup(pathname);

	return TRUE;
}
