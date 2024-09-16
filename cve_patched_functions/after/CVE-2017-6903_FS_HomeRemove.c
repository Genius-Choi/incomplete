void FS_HomeRemove( const char *homePath ) {
	FS_CheckFilenameIsMutable( homePath, __func__ );

	remove( FS_BuildOSPath( fs_homepath->string,
			fs_gamedir, homePath ) );
}
