<?php
/*
Plugin Name: Facebook Button
Plugin URI: http://bestwebsoft.com/plugin/
Description: Put Facebook Button in to your post.
Author: BestWebSoft
Version: 2.33
Author URI: http://bestwebsoft.com/
License: GPLv2 or later
*/

/*  Copyright 2014  BestWebSoft  ( http://support.bestwebsoft.com )

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License, version 2, as 
    published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

if ( ! function_exists( 'fcbkbttn_add_pages' ) ) {
	function fcbkbttn_add_pages() {
		global $bstwbsftwppdtplgns_options, $wpmu, $bstwbsftwppdtplgns_added_menu;
		$bws_menu_info = get_plugin_data( plugin_dir_path( __FILE__ ) . "bws_menu/bws_menu.php" );
		$bws_menu_version = $bws_menu_info["Version"];
		$base = plugin_basename(__FILE__);

		if ( ! isset( $bstwbsftwppdtplgns_options ) ) {
			if ( 1 == $wpmu ) {
				if ( ! get_site_option( 'bstwbsftwppdtplgns_options' ) )
					add_site_option( 'bstwbsftwppdtplgns_options', array(), '', 'yes' );
				$bstwbsftwppdtplgns_options = get_site_option( 'bstwbsftwppdtplgns_options' );
			} else {
				if ( ! get_option( 'bstwbsftwppdtplgns_options' ) )
					add_option( 'bstwbsftwppdtplgns_options', array(), '', 'yes' );
				$bstwbsftwppdtplgns_options = get_option( 'bstwbsftwppdtplgns_options' );
			}
		}

		if ( isset( $bstwbsftwppdtplgns_options['bws_menu_version'] ) ) {
			$bstwbsftwppdtplgns_options['bws_menu']['version'][ $base ] = $bws_menu_version;
			unset( $bstwbsftwppdtplgns_options['bws_menu_version'] );
			update_option( 'bstwbsftwppdtplgns_options', $bstwbsftwppdtplgns_options, '', 'yes' );
			require_once( dirname( __FILE__ ) . '/bws_menu/bws_menu.php' );
		} else if ( ! isset( $bstwbsftwppdtplgns_options['bws_menu']['version'][ $base ] ) || $bstwbsftwppdtplgns_options['bws_menu']['version'][ $base ] < $bws_menu_version ) {
			$bstwbsftwppdtplgns_options['bws_menu']['version'][ $base ] = $bws_menu_version;
			update_option( 'bstwbsftwppdtplgns_options', $bstwbsftwppdtplgns_options, '', 'yes' );
			require_once( dirname( __FILE__ ) . '/bws_menu/bws_menu.php' );
		} else if ( ! isset( $bstwbsftwppdtplgns_added_menu ) ) {
			$plugin_with_newer_menu = $base;
			foreach ( $bstwbsftwppdtplgns_options['bws_menu']['version'] as $key => $value ) {
				if ( $bws_menu_version < $value && is_plugin_active( $base ) ) {
					$plugin_with_newer_menu = $key;
				}
			}
			$plugin_with_newer_menu = explode( '/', $plugin_with_newer_menu );
			$wp_content_dir = defined( 'WP_CONTENT_DIR' ) ? basename( WP_CONTENT_DIR ) : 'wp-content';
			if ( file_exists( ABSPATH . $wp_content_dir . '/plugins/' . $plugin_with_newer_menu[0] . '/bws_menu/bws_menu.php' ) )
				require_once( ABSPATH . $wp_content_dir . '/plugins/' . $plugin_with_newer_menu[0] . '/bws_menu/bws_menu.php' );
			else
				require_once( dirname( __FILE__ ) . '/bws_menu/bws_menu.php' );
			$bstwbsftwppdtplgns_added_menu = true;			
		}

		add_menu_page( 'BWS Plugins', 'BWS Plugins', 'manage_options', 'bws_plugins', 'bws_add_menu_render', plugins_url( "images/px.png", __FILE__ ), 1001 );
		add_submenu_page( 'bws_plugins', __( 'Facebook Button Settings', 'facebook' ), __( 'Facebook Button', 'facebook' ), 'manage_options', "facebook-button-plugin.php", 'fcbkbttn_settings_page' );
	}
}

/* Initialization */
if ( ! function_exists( 'fcbkbttn_init' ) ) {
	function fcbkbttn_init() {
		global $wpmu, $fcbkbttn_options;
		/* Internationalization, first(!) */
		load_plugin_textdomain( 'facebook', false, dirname( plugin_basename( __FILE__ ) ) . '/languages/' );
		/* Get options from the database */
		if ( ! is_admin() || ( isset( $_GET['page'] ) && "facebook-button-plugin.php" == $_GET['page'] ) ) {
			/* Get/Register and check settings for plugin */
			fcbkbttn_settings();
		}
	}
}
/* End function init */

if ( ! function_exists( 'fcbkbttn_admin_init' ) ) {
	function fcbkbttn_admin_init() {
		/* Add variable for bws_menu */
		global $bws_plugin_info, $fcbkbttn_plugin_info;

		if ( ! $fcbkbttn_plugin_info )
			$fcbkbttn_plugin_info = get_plugin_data( __FILE__ );
		
		if ( ! isset( $bws_plugin_info ) || empty( $bws_plugin_info ) )	{		
			$bws_plugin_info = array( 'id' => '78', 'version' => $fcbkbttn_plugin_info["Version"] );
		}
		/* Function check if plugin is compatible with current WP version  */
		fcbkbttn_version_check();
	}
}

if ( ! function_exists( 'fcbkbttn_settings' ) ) {
	function fcbkbttn_settings() {
		global $wpmu, $fcbkbttn_options, $fcbkbttn_plugin_info;

		if ( ! $fcbkbttn_plugin_info ) {
			if ( ! function_exists( 'get_plugin_data' ) )
				require_once( ABSPATH . 'wp-admin/includes/plugin.php' );

			$fcbkbttn_plugin_info = get_plugin_data( __FILE__ );	
		}

		$fcbkbttn_options_default = array(
			'plugin_option_version' => $fcbkbttn_plugin_info["Version"],
			'link'					=>	'',
			'my_page'				=>	1,
			'like'					=>	1,
			'share'					=>	0,
			'where'					=>	'',
			'display_option'		=>	'',
			'count_icon'			=>	1,
			'extention'				=>	'png',
			'fb_img_link'			=>	plugins_url( "images/standart-facebook-ico.png", __FILE__ ),
			'locale' 				=>	'en_US',
			'html5'					=>	0
		);
		/* Install the option defaults */
		if ( 1 == $wpmu ) {
			if ( ! get_site_option( 'fcbk_bttn_plgn_options' ) ) {
				if ( false !== get_site_option( 'fcbk_bttn_plgn_options_array' ) ) {
					$old_options = get_site_option( 'fcbk_bttn_plgn_options_array' );
					foreach ( $fcbkbttn_options_default as $key => $value ) {
						if ( isset( $old_options['fcbk_bttn_plgn_' . $key] ) )
						$fcbkbttn_options_default[$key] = $old_options['fcbk_bttn_plgn_' . $key];
					}
					update_site_option( 'fcbk_bttn_plgn_options', $fcbkbttn_options_default );
					delete_site_option( 'fcbk_bttn_plgn_options_array' );
				}
				add_site_option( 'fcbk_bttn_plgn_options', $fcbkbttn_options_default, '', 'yes' );
			}
		} else {
			if ( ! get_option( 'fcbk_bttn_plgn_options' ) ) {
				if ( false !== get_option( 'fcbk_bttn_plgn_options_array' ) ) {
					$old_options = get_option( 'fcbk_bttn_plgn_options_array' );
					foreach ( $fcbkbttn_options_default as $key => $value ) {
						if ( isset( $old_options['fcbk_bttn_plgn_' . $key] ) )
						$fcbkbttn_options_default[$key] = $old_options['fcbk_bttn_plgn_' . $key];
					}
					update_option( 'fcbk_bttn_plgn_options', $fcbkbttn_options_default );
					delete_option( 'fcbk_bttn_plgn_options_array' );
				}
				add_option( 'fcbk_bttn_plgn_options', $fcbkbttn_options_default, '', 'yes' );
			}
		}
		/* Get options from the database */
		if ( 1 == $wpmu )
			$fcbkbttn_options = get_site_option( 'fcbk_bttn_plgn_options' );
		else
			$fcbkbttn_options = get_option( 'fcbk_bttn_plgn_options' );

		if ( ! isset( $fcbkbttn_options['plugin_option_version'] ) || $fcbkbttn_options['plugin_option_version'] != $fcbkbttn_plugin_info["Version"] ) {
			if ( stristr( $fcbkbttn_options['fb_img_link'], 'standart-facebook-ico.jpg' ) )
				$fcbkbttn_options['fb_img_link'] = plugins_url( "images/standart-facebook-ico.png", __FILE__ );	

			if ( stristr( $fcbkbttn_options['fb_img_link'], 'img/' ) )
				$fcbkbttn_options['fb_img_link'] = plugins_url( str_replace( 'img/', 'images/', $fcbkbttn_options['fb_img_link'] ), __FILE__ );	

			$fcbkbttn_options = array_merge( $fcbkbttn_options_default, $fcbkbttn_options );
			$fcbkbttn_options['plugin_option_version'] = $fcbkbttn_plugin_info["Version"];
			update_option( 'fcbk_bttn_plgn_options', $fcbkbttn_options );
		}
	}
}

/* Function check if plugin is compatible with current WP version  */
if ( ! function_exists ( 'fcbkbttn_version_check' ) ) {
	function fcbkbttn_version_check() {
		global $wp_version, $fcbkbttn_plugin_info;
		$require_wp		=	"3.0"; /* Wordpress at least requires version */
		$plugin			=	plugin_basename( __FILE__ );
	 	if ( version_compare( $wp_version, $require_wp, "<" ) ) {
			if ( is_plugin_active( $plugin ) ) {
				deactivate_plugins( $plugin );
				wp_die( "<strong>" . $fcbkbttn_plugin_info['Name'] . " </strong> " . __( 'requires', 'facebook' ) . " <strong>WordPress " . $require_wp . "</strong> " . __( 'or higher, that is why it has been deactivated! Please upgrade WordPress and try again.', 'facebook') . "<br /><br />" . __( 'Back to the WordPress', 'facebook') . " <a href='" . get_admin_url( null, 'plugins.php' ) . "'>" . __( 'Plugins page', 'facebook') . "</a>." );
			}
		}
	}
}

/* Function formed content of the plugin's admin page. */
if ( ! function_exists( 'fcbkbttn_settings_page' ) ) {
	function fcbkbttn_settings_page() {
		global $fcbkbttn_options, $wp_version, $fcbkbttn_plugin_info;
		$copy = false;
		$message = $error = "";
		$upload_dir = wp_upload_dir();

		if ( isset( $_REQUEST['fcbkbttn_form_submit'] ) && check_admin_referer( plugin_basename( __FILE__ ), 'fcbkbttn_nonce_name' ) ) {
			/* Takes all the changed settings on the plugin's admin page and saves them in array 'fcbk_bttn_plgn_options'. */
			if ( isset( $_REQUEST['fcbkbttn_where'] ) && isset( $_REQUEST['fcbkbttn_link'] ) && isset( $_REQUEST['fcbkbttn_display_option'] ) ) {
				$fcbkbttn_options['link']			=	$_REQUEST['fcbkbttn_link'];
				$fcbkbttn_options['where']			=	$_REQUEST['fcbkbttn_where'];
				$fcbkbttn_options['display_option']	=	$_REQUEST['fcbkbttn_display_option'];
				if ( 'standart' == $fcbkbttn_options['display_option'] ) {
					$fcbkbttn_options['fb_img_link'] = plugins_url( 'images/standart-facebook-ico.png', __FILE__ );
				}				
				$fcbkbttn_options['my_page']		=	isset( $_REQUEST['fcbkbttn_my_page'] ) ? 1 : 0 ;
				$fcbkbttn_options['like']			=	isset( $_REQUEST['fcbkbttn_like'] ) ? 1 : 0 ;
				$fcbkbttn_options['share']			=	isset( $_REQUEST['fcbkbttn_share'] ) ? 1 : 0 ;
				$fcbkbttn_options['locale']			=	$_REQUEST['fcbkbttn_locale'];
				$fcbkbttn_options['html5']			= 	$_REQUEST['fcbkbttn_html5'];
				if ( isset( $_FILES['uploadfile']['tmp_name'] ) &&  $_FILES['uploadfile']['tmp_name'] != "" ) {
					$fcbkbttn_options['count_icon']	=	$fcbkbttn_options['count_icon'] + 1;
					$file_ext = wp_check_filetype( $_FILES['uploadfile']['name'] );
					$fcbkbttn_options['extention'] = $file_ext['ext'];
				}

				if ( 2 < $fcbkbttn_options['count_icon'] )
					$fcbkbttn_options['count_icon']	=	1;
				update_option( 'fcbk_bttn_plgn_options', $fcbkbttn_options );
				$message = __( "Settings saved", 'facebook' );
			}
			/* Form options */
			if ( isset( $_FILES['uploadfile']['tmp_name'] ) &&  "" != $_FILES['uploadfile']['tmp_name'] ) {
				if ( ! $upload_dir["error"] ) {
					$fcbkbttn_cstm_mg_folder = $upload_dir['basedir'] . '/facebook-image';
					if ( ! is_dir( $fcbkbttn_cstm_mg_folder ) ) {
						wp_mkdir_p( $fcbkbttn_cstm_mg_folder, 0755 );
					}
				}				
				$max_image_width	=	100;
				$max_image_height	=	40;
				$max_image_size		=	32 * 1024;
				$valid_types 		=	array( 'jpg', 'jpeg', 'png' );
				/* Construction to rename downloading file */
				$new_name			=	'facebook-ico' . $fcbkbttn_options['count_icon'];
				$new_ext			=	wp_check_filetype( $_FILES['uploadfile']['name'] );
				$namefile			=	$new_name . '.' . $new_ext['ext'];
				/* $uploaddir			=	$_REQUEST['home'] . 'wp-content/plugins/facebook-button-plugin/images/'; The directory in which we will take the file: */
				$uploadfile			=	$fcbkbttn_cstm_mg_folder . '/' . $namefile;

				/* Checks is file download initiated by user */
				if ( isset( $_FILES['uploadfile'] ) && 'custom' == $_REQUEST['fcbkbttn_display_option'] ) {
					/* Checking is allowed download file given parameters */
					if ( is_uploaded_file( $_FILES['uploadfile']['tmp_name'] ) ) {
						$filename	=	$_FILES['uploadfile']['tmp_name'];
						$ext		=	substr( $_FILES['uploadfile']['name'], 1 + strrpos( $_FILES['uploadfile']['name'], '.' ) );
						if ( filesize( $filename ) > $max_image_size ) {
							$error	=	__( "Error: File size > 32K", 'facebook' );
						}
						elseif ( ! in_array( $ext, $valid_types ) ) {
							$error	=	__( "Error: Invalid file type", 'facebook' );
						} else {
							$size	=	GetImageSize( $filename );
							if ( ( $size ) && ( $size[0] <= $max_image_width ) && ( $size[1] <= $max_image_height ) ) {
								/* If file satisfies requirements, we will move them from temp to your plugin folder and rename to 'facebook_ico.jpg' */
								if ( move_uploaded_file( $_FILES['uploadfile']['tmp_name'], $uploadfile ) ) {
									$message .= '. ' . __( "Upload successful.", 'facebook' );
									fcbkbttn_update_option();
								} else {
									$error = __( "Error: moving file failed", 'facebook' );
								}
							} else {
								$error = __( "Error: check image width or height", 'facebook' );
							}
						}
					} else {
						$error = __( "Uploading Error: check image properties", 'facebook' );
					}
				}
			}
		}
		/* GO PRO */
		if ( isset( $_GET['action'] ) && 'go_pro' == $_GET['action'] ) {
			global $wpmu;

			$bws_license_key = ( isset( $_POST['bws_license_key'] ) ) ? trim( $_POST['bws_license_key'] ) : "";
			$bstwbsftwppdtplgns_options_defaults = array();
			if ( 1 == $wpmu ) {
				if ( !get_site_option( 'bstwbsftwppdtplgns_options' ) )
					add_site_option( 'bstwbsftwppdtplgns_options', $bstwbsftwppdtplgns_options_defaults, '', 'yes' );
				$bstwbsftwppdtplgns_options = get_site_option( 'bstwbsftwppdtplgns_options' );
			} else {
				if ( !get_option( 'bstwbsftwppdtplgns_options' ) )
					add_option( 'bstwbsftwppdtplgns_options', $bstwbsftwppdtplgns_options_defaults, '', 'yes' );
				$bstwbsftwppdtplgns_options = get_option( 'bstwbsftwppdtplgns_options' );
			}

			if ( isset( $_POST['bws_license_submit'] ) && check_admin_referer( plugin_basename( __FILE__ ), 'bws_license_nonce_name' ) ) {
				if ( '' != $bws_license_key ) { 
					if ( strlen( $bws_license_key ) != 18 ) {
						$error = __( "Wrong license key", 'facebook' );
					} else {
						$bws_license_plugin = trim( $_POST['bws_license_plugin'] );	
						if ( isset( $bstwbsftwppdtplgns_options['go_pro'][ $bws_license_plugin ]['count'] ) && $bstwbsftwppdtplgns_options['go_pro'][ $bws_license_plugin ]['time'] < ( time() + (24 * 60 * 60) ) ) {
							$bstwbsftwppdtplgns_options['go_pro'][ $bws_license_plugin ]['count'] = $bstwbsftwppdtplgns_options['go_pro'][ $bws_license_plugin ]['count'] + 1;
						} else {
							$bstwbsftwppdtplgns_options['go_pro'][ $bws_license_plugin ]['count'] = 1;
							$bstwbsftwppdtplgns_options['go_pro'][ $bws_license_plugin ]['time'] = time();
						}	

						/* download Pro */
						if ( ! function_exists( 'get_plugins' ) )
							require_once( ABSPATH . 'wp-admin/includes/plugin.php' );
						if ( ! function_exists( 'is_plugin_active_for_network' ) )
							require_once( ABSPATH . '/wp-admin/includes/plugin.php' );
						$all_plugins = get_plugins();
						$active_plugins = get_option( 'active_plugins' );
						
						if ( ! array_key_exists( $bws_license_plugin, $all_plugins ) ) {
							$current = get_site_transient( 'update_plugins' );
							if ( is_array( $all_plugins ) && !empty( $all_plugins ) && isset( $current ) && is_array( $current->response ) ) {
								$to_send = array();
								$to_send["plugins"][ $bws_license_plugin ] = array();
								$to_send["plugins"][ $bws_license_plugin ]["bws_license_key"] = $bws_license_key;
								$to_send["plugins"][ $bws_license_plugin ]["bws_illegal_client"] = true;
								$options = array(
									'timeout' => ( ( defined('DOING_CRON') && DOING_CRON ) ? 30 : 3 ),
									'body' => array( 'plugins' => serialize( $to_send ) ),
									'user-agent' => 'WordPress/' . $wp_version . '; ' . get_bloginfo( 'url' ) );
								$raw_response = wp_remote_post( 'http://bestwebsoft.com/wp-content/plugins/paid-products/plugins/update-check/1.0/', $options );

								if ( is_wp_error( $raw_response ) || 200 != wp_remote_retrieve_response_code( $raw_response ) ) {
									$error = __( "Something went wrong. Try again later. If the error will appear again, please, contact us <a href=http://support.bestwebsoft.com>BestWebSoft</a>. We are sorry for inconvenience.", 'facebook' );
								} else {
									$response = maybe_unserialize( wp_remote_retrieve_body( $raw_response ) );
									
									if ( is_array( $response ) && ! empty( $response ) ) {
										foreach ( $response as $key => $value ) {
											if ( "wrong_license_key" == $value->package ) {
												$error = __( "Wrong license key", 'facebook' ); 
											} elseif ( "wrong_domain" == $value->package ) {
												$error = __( "This license key is bind to another site", 'facebook' );
											} elseif ( "you_are_banned" == $value->package ) {
												$error = __( "Unfortunately, you have exceeded the number of available tries. Please, upload the plugin manually.", 'facebook' );
											}
										}
										if ( '' == $error ) {
											global $wpmu;																					
											$bstwbsftwppdtplgns_options[ $bws_license_plugin ] = $bws_license_key;

											$url = 'http://bestwebsoft.com/wp-content/plugins/paid-products/plugins/downloads/?bws_first_download=' . $bws_license_plugin . '&bws_license_key=' . $bws_license_key . '&download_from=5';
											$uploadDir = wp_upload_dir();
											$zip_name = explode( '/', $bws_license_plugin );
										    if ( file_put_contents( $uploadDir["path"] . "/" . $zip_name[0] . ".zip", file_get_contents( $url ) ) ) {
										    	@chmod( $uploadDir["path"] . "/" . $zip_name[0] . ".zip", octdec( 755 ) );
										    	if ( class_exists( 'ZipArchive' ) ) {
													$zip = new ZipArchive();
													if ( $zip->open( $uploadDir["path"] . "/" . $zip_name[0] . ".zip" ) === TRUE ) {
														$zip->extractTo( WP_PLUGIN_DIR );
														$zip->close();
													} else {
														$error = __( "Failed to open the zip archive. Please, upload the plugin manually", 'facebook' );
													}								
												} elseif ( class_exists( 'Phar' ) ) {
													$phar = new PharData( $uploadDir["path"] . "/" . $zip_name[0] . ".zip" );
													$phar->extractTo( WP_PLUGIN_DIR );
												} else {
													$error = __( "Your server does not support either ZipArchive or Phar. Please, upload the plugin manually", 'facebook' );
												}
												@unlink( $uploadDir["path"] . "/" . $zip_name[0] . ".zip" );										    
											} else {
												$error = __( "Failed to download the zip archive. Please, upload the plugin manually", 'facebook' );
											}

											/* activate Pro */
											if ( file_exists( WP_PLUGIN_DIR . '/' . $zip_name[0] ) ) {			
												array_push( $active_plugins, $bws_license_plugin );
												update_option( 'active_plugins', $active_plugins );
												$pro_plugin_is_activated = true;
											} elseif ( '' == $error ) {
												$error = __( "Failed to download the zip archive. Please, upload the plugin manually", 'facebook' );
											}																				
										}
									} else {
										$error = __( "Something went wrong. Try again later or upload the plugin manually. We are sorry for inconvienience.", 'facebook' ); 
					 				}
					 			}
				 			}
						} else {
							/* activate Pro */
							if ( ! ( in_array( $bws_license_plugin, $active_plugins ) || is_plugin_active_for_network( $bws_license_plugin ) ) ) {			
								array_push( $active_plugins, $bws_license_plugin );
								update_option( 'active_plugins', $active_plugins );
								$pro_plugin_is_activated = true;
							}						
						}
						update_option( 'bstwbsftwppdtplgns_options', $bstwbsftwppdtplgns_options, '', 'yes' );
			 		}
			 	} else {
		 			$error = __( "Please, enter Your license key", 'facebook' );
		 		}
		 	}
		}
		$lang_codes = array(
			"af_ZA" => 'Afrikaans', "ar_AR" => 'العربية', "ay_BO" => 'Aymar aru', "az_AZ" => 'Azərbaycan dili', "be_BY" => 'Беларуская', "bg_BG" => 'Български', "bn_IN" => 'বাংলা', "bs_BA" => 'Bosanski', "ca_ES" => 'Català', "ck_US" => 'Cherokee', "cs_CZ" => 'Čeština', "cy_GB" => 'Cymraeg', "da_DK" => 'Dansk', "de_DE" => 'Deutsch', "el_GR" => 'Ελληνικά', "en_US" => 'English', "en_PI" => 'English (Pirate)', "eo_EO" => 'Esperanto', "es_CL" => 'Español (Chile)', "es_CO" => 'Español (Colombia)', "es_ES" => 'Español (España)', "es_LA" => 'Español', "es_MX" => 'Español (México)', "es_VE" => 'Español (Venezuela)', "et_EE" => 'Eesti', "eu_ES" => 'Euskara', "fa_IR" => 'فارسی', "fb_LT" => 'Leet Speak', "fi_FI" => 'Suomi', "fo_FO" => 'Føroyskt', "fr_CA" => 'Français (Canada)', "fr_FR" => 'Français (France)', "fy_NL" => 'Frysk', "ga_IE" => 'Gaeilge', "gl_ES" => 'Galego', "gn_PY" => "Avañe'ẽ", "gu_IN" => 'ગુજરાતી', "gx_GR" => 'Ἑλληνική ἀρχαία', "he_IL" => 'עברית', "hi_IN" => 'हिन्दी', "hr_HR" => 'Hrvatski', "hu_HU" => 'Magyar', "hy_AM" => 'Հայերեն', "id_ID" => 'Bahasa Indonesia', "is_IS" => 'Íslenska', "it_IT" => 'Italiano', "ja_JP" => '日本語', "jv_ID" => 'Basa Jawa', "ka_GE" => 'ქართული', "kk_KZ" => 'Қазақша', "km_KH" => 'ភាសាខ្មែរ', "kn_IN" => 'ಕನ್ನಡ', "ko_KR" => '한국어', "ku_TR" => 'Kurdî', "la_VA" => 'lingua latina', "li_NL" => 'Limburgs', "lt_LT" => 'Lietuvių', "lv_LV" => 'Latviešu', "mg_MG" => 'Malagasy', "mk_MK" => 'Македонски', "ml_IN" => 'മലയാളം', "mn_MN" => 'Монгол', "mr_IN" => 'मराठी', "ms_MY" => 'Bahasa Melayu', "mt_MT" => 'Malti', "nb_NO" => 'Norsk (bokmål)', "ne_NP" => 'नेपाली', "nl_BE" => 'Nederlands (België)', "nl_NL" => 'Nederlands', "nn_NO" => 'Norsk (nynorsk)', "pa_IN" => 'ਪੰਜਾਬੀ', "pl_PL" => 'Polski', "ps_AF" => 'پښتو', "pt_BR" => 'Português (Brasil)', "pt_PT" => 'Português (Portugal)', "qu_PE" => 'Qhichwa', "rm_CH" => 'Rumantsch', "ro_RO" => 'Română', "ru_RU" => 'Русский', "sa_IN" => 'संस्कृतम्', "se_NO" => 'Davvisámegiella', "sk_SK" => 'Slovenčina', "sl_SI" => 'Slovenščina', "so_SO" => 'Soomaaliga', "sq_AL" => 'Shqip', "sr_RS" => 'Српски', "sv_SE" => 'Svenska', "sw_KE" => 'Kiswahili', "sy_SY" => 'ܐܪܡܝܐ', "ta_IN" => 'தமிழ்', "te_IN" => 'తెలుగు', "tg_TJ" => 'тоҷикӣ', "th_TH" => 'ภาษาไทย', "tl_PH" => 'Filipino', "tl_ST" => 'tlhIngan-Hol', "tr_TR" => 'Türkçe', "tt_RU" => 'Татарча', "uk_UA" => 'Українська', "ur_PK" => 'اردو', "uz_UZ" => "O'zbek", "vi_VN" => 'Tiếng Việt', "yi_DE" => 'ייִדיש', "zh_CN" => '中文(简体)', "zh_HK" => '中文(香港)', "zh_TW" => '中文(台灣)', "zu_ZA" => 'isiZulu' 											
			);
		?>
		<div class="wrap">
			<div class="icon32 icon32-bws" id="icon-options-general"></div>
			<h2><?php _e( "Facebook Button Settings", 'facebook' ); ?></h2>
			<h2 class="nav-tab-wrapper">
				<a class="nav-tab<?php if ( ! isset( $_GET['action'] ) ) echo ' nav-tab-active'; ?>" href="admin.php?page=facebook-button-plugin.php"><?php _e( 'Settings', 'facebook' ); ?></a>
				<a class="nav-tab<?php if ( isset( $_GET['action'] ) && 'extra' == $_GET['action'] ) echo ' nav-tab-active'; ?>" href="admin.php?page=facebook-button-plugin.php&amp;action=extra"><?php _e( 'Extra settings', 'facebook' ); ?></a>
				<a class="nav-tab" href="http://bestwebsoft.com/plugin/facebook-like-button-plugin/#faq" target="_blank" ><?php _e( 'FAQ', 'facebook' ); ?></a>
				<a class="nav-tab bws_go_pro_tab<?php if ( isset( $_GET['action'] ) && 'go_pro' == $_GET['action'] ) echo ' nav-tab-active'; ?>" href="admin.php?page=facebook-button-plugin.php&amp;action=go_pro"><?php _e( 'Go PRO', 'facebook' ); ?></a>
			</h2>
			<div class="updated fade" <?php if ( empty( $message ) || "" != $error ) echo "style=\"display:none\""; ?>><p><strong><?php echo $message; ?></strong></p></div>
			<div id="fcbkbttn_settings_notice" class="updated fade" style="display:none"><p><strong><?php _e( "Notice:", 'facebook' ); ?></strong> <?php _e( "The plugin's settings have been changed. In order to save them please don't forget to click the 'Save Changes' button.", 'facebook' ); ?></p></div>
			<div class="error" <?php if ( "" == $error ) echo "style=\"display:none\""; ?>><p><strong><?php echo $error; ?></strong></p></div>
			<?php if ( ! isset( $_GET['action'] ) ) { ?>
				<form name="form1" method="post" action="admin.php?page=facebook-button-plugin.php" enctype="multipart/form-data" id="fcbkbttn_settings_form">
					<table class="form-table">
						<tr valign="top">
							<th scope="row"><?php _e( "Your Facebook ID:", 'facebook' ); ?></th>
							<td>
								<input name='fcbkbttn_link' type='text' value='<?php echo $fcbkbttn_options['link']; ?>' />
							</td>
						</tr>
						<tr valign="top">
							<th scope="row"><?php _e( "Display button:", 'facebook' ); ?></th>
							<td>
								<label><input name='fcbkbttn_my_page' type='checkbox' value='1' <?php if ( 1 == $fcbkbttn_options['my_page'] ) echo 'checked="checked "'; ?>/> <?php _e( "My Page", 'facebook' ); ?></label><br />
								<label><input name='fcbkbttn_like' type='checkbox' value='1' <?php if ( 1 == $fcbkbttn_options['like'] ) echo 'checked="checked "'; ?>/> <?php _e( "Like", 'facebook' ); ?></label><br />
								<label><input name='fcbkbttn_share' type='checkbox' value='1' <?php if ( 1 == $fcbkbttn_options['share'] ) echo 'checked="checked "'; ?>/> <?php _e( "Share", 'facebook' ); ?></label>
							</td>
						</tr>
						<tr>
							<th>
								<?php _e( "Choose display settings:", 'facebook' ); ?>
							</th>
							<td>
								<?php if ( scandir( $upload_dir['basedir'] ) && is_writable( $upload_dir['basedir'] ) ) { ?>
									<select name="fcbkbttn_display_option" onchange="if ( this . value == 'custom' ) { getElementById ( 'fcbkbttn_display_option_custom' ) . style.display = 'table-row'; } else { getElementById ( 'fcbkbttn_display_option_custom' ) . style.display = 'none'; }">
										<option <?php if ( 'standart' == $fcbkbttn_options['display_option'] ) echo 'selected="selected"'; ?> value="standart"><?php _e( "Standard Facebook image", 'facebook' ); ?></option>
										<option <?php if ( 'custom' == $fcbkbttn_options['display_option'] ) echo 'selected="selected"'; ?> value="custom"><?php _e( "Custom Facebook image", 'facebook' ); ?></option>
									</select>
								<?php } else {
									echo __( "To use custom image you need to setup permissions to upload directory of your site", 'facebook' ) . " - " .$upload_dir['basedir'];
								} ?>
							</td>
						</tr>
						<tr>
							<th>
								<?php _e( "Current image:", 'facebook' ); ?>
							</th>
							<td>
								<img src="<?php echo $fcbkbttn_options['fb_img_link']; ?>" style="margin-left:2px;" />
							</td>
						</tr>
						<tr id="fcbkbttn_display_option_custom" <?php if ( 'custom' == $fcbkbttn_options['display_option'] ) { echo ( 'style="display:table-row"' ); } else { echo ( 'style="display:none"' ); } ?>>
							<th scope="row">
								<?php _e( "Facebook image:", 'facebook' ); ?>
							</th>
							<td>
								<!-- <input type="hidden" name="MAX_FILE_SIZE" value="64000"/>
								<input type="hidden" name="home" value="<?php echo ABSPATH ; ?>"/> -->
								<input name="uploadfile" type="file" /><br />
								<span style="color: rgb(136, 136, 136); font-size: 10px;"><?php _e( 'Image properties: max image width:100px; max image height:40px; max image size:32Kb; image types:"jpg", "jpeg", "png".', 'facebook' ); ?></span>
							</td>
						</tr>
						<tr>
							<th>
								<?php _e( "Facebook Button Position:", 'facebook' ); ?>
							</th>
							<td>
								<select name="fcbkbttn_where" onchange="if ( this . value == 'shortcode' ) { getElementById ( 'shortcode' ) . style.display = 'inline'; } else { getElementById ( 'shortcode' ) . style.display = 'none'; }">
									<option <?php if ( 'before' == $fcbkbttn_options['where']  ) echo 'selected="selected"'; ?> value="before"><?php _e( "Before", 'facebook' ); ?></option>
									<option <?php if ( 'after' == $fcbkbttn_options['where']  ) echo 'selected="selected"'; ?> value="after"><?php _e( "After", 'facebook' ); ?></option>
									<option <?php if ( 'beforeandafter' == $fcbkbttn_options['where']  ) echo 'selected="selected"'; ?> value="beforeandafter"><?php _e( "Before and After", 'facebook' ); ?></option>
									<option <?php if ( 'shortcode' == $fcbkbttn_options['where'] ) echo 'selected="selected"'; ?> value="shortcode"><?php _e( "Shortcode", 'facebook' ); ?></option>
								</select>
								<span id="shortcode" style="color: rgb(136, 136, 136); font-size: 10px; <?php if ( $fcbkbttn_options['where'] == 'shortcode' ) { echo ( 'display:inline' ); } else { echo ( 'display:none' ); }?>"><?php _e( "If you would like to add a Facebook button to your website, just copy and paste this shortcode into your post or page:", 'facebook' ); ?> [fb_button].</span>
							</td>
						</tr>
						<tr>
							<th>
								<?php _e( "Facebook Button language:", 'facebook' ); ?>
							</th>
							<td>
								<select name="fcbkbttn_locale">
								<?php foreach ( $lang_codes as $key => $val ) {
									echo '<option value="' . $key . '"';
									if ( $key == $fcbkbttn_options['locale'] )
										echo ' selected="selected"';
									echo '>' . esc_html ( $val ) . '</option>';
								} ?>
								</select>
								<span id="shortcode" style="color: rgb(136, 136, 136); font-size: 10px; display:inline"><?php _e( "Change the language of Facebook Like Button", 'facebook' ); ?></span>
							</td>
						</tr>
						<tr valign="top">
							<th scope="row"><?php _e( "Html tag for Like Button:", 'facebook' ); ?></th>
							<td>
								<label><input name='fcbkbttn_html5' type='radio' value='0' <?php if ( 0 == $fcbkbttn_options['html5'] ) echo 'checked="checked "'; ?> /><?php echo "<code>&lt;fb:like&gt;</code>"; ?></label><br />
								<label><input name='fcbkbttn_html5' type='radio' value='1' <?php if ( 1 == $fcbkbttn_options['html5'] ) echo 'checked="checked "'; ?> /><?php echo "<code>&lt;div&gt;</code>"; ?></label>
								<span style="color: rgb(136, 136, 136); font-size: 10px; display:inline">(<?php _e( "Use this tag to improve validation of your site", 'facebook' ); ?>)</span>
							</td>
						</tr>
					</table>
					<input type="hidden" name="fcbkbttn_form_submit" value="submit" />
					<p class="submit">
						<input type="submit" class="button-primary" value="<?php _e( 'Save Changes', 'facebook' ); ?>" />
					</p>
					<?php wp_nonce_field( plugin_basename( __FILE__ ), 'fcbkbttn_nonce_name' ); ?>
				</form>
				<div class="bws-plugin-reviews">
					<div class="bws-plugin-reviews-rate">
						<?php _e( 'If you enjoy our plugin, please give it 5 stars on WordPress', 'facebook' ); ?>: 
						<a href="http://wordpress.org/support/view/plugin-reviews/facebook-button-plugin" target="_blank" title="Facebook Button reviews"><?php _e( 'Rate the plugin', 'facebook' ); ?></a>
					</div>
					<div class="bws-plugin-reviews-support">
						<?php _e( 'If there is something wrong about it, please contact us', 'facebook' ); ?>: 
						<a href="http://support.bestwebsoft.com">http://support.bestwebsoft.com</a>
					</div>
				</div>
			<?php } elseif ( 'extra' == $_GET['action'] ) { ?>
				<div class="bws_pro_version_bloc">
					<div class="bws_pro_version_table_bloc">	
						<div class="bws_table_bg"></div>											
						<table class="form-table bws_pro_version">
							<tr valign="top">
								<td colspan="2">
									<?php _e( 'Please choose the necessary post types (or single pages) where Facebook button will be displayed:', 'facebook' ); ?>
								</td>
							</tr>
							<tr valign="top">
								<td colspan="2">
									<label>
										<input disabled="disabled" checked="checked" type="checkbox" name="jstree_url" value="1" />
										<?php _e( "Show URL for pages", 'facebook' );?>
									</label>
								</td>
							</tr>
							<tr valign="top">
								<td colspan="2">
									<img src="<?php echo plugins_url( 'images/pro_screen_1.png', __FILE__ ); ?>" alt="<?php _e( "Example of the site's pages tree", 'facebook' ); ?>" title="<?php _e( "Example of site pages' tree", 'facebook' ); ?>" />
								</td>
							</tr>
							<tr valign="top">
								<td colspan="2">
									<input disabled="disabled" type="submit" class="button-primary" value="<?php _e( 'Save Changes', 'facebook' ); ?>" />
								</td>
							</tr>
							<tr valign="top">
								<th scope="row" colspan="2">
									* <?php _e( 'If you upgrade to Pro version all your settings will be saved.', 'facebook' ); ?>
								</th>
							</tr>				
						</table>	
					</div>
					<div class="bws_pro_version_tooltip">
						<div class="bws_info">
							<?php _e( 'Unlock premium options by upgrading to a PRO version.', 'facebook' ); ?> 
							<a href="http://bestwebsoft.com/plugin/facebook-like-button-pro/?k=427287ceae749cbd015b4bba6041c4b8&pn=78&v=<?php echo $fcbkbttn_plugin_info["Version"]; ?>&wp_v=<?php echo $wp_version; ?>" target="_blank" title="Facebook Like Button Pro"><?php _e( 'Learn More', 'facebook' ); ?></a>				
						</div>
						<a class="bws_button" href="http://bestwebsoft.com/plugin/facebook-like-button-pro/?k=427287ceae749cbd015b4bba6041c4b8&pn=78&v=<?php echo $fcbkbttn_plugin_info["Version"]; ?>&wp_v=<?php echo $wp_version; ?>#purchase" target="_blank" title="Facebook Like Button Pro">
							<?php _e( 'Go', 'facebook' ); ?> <strong>PRO</strong>
						</a>	
						<div class="clear"></div>					
					</div>
				</div>
			<?php } elseif ( 'go_pro' == $_GET['action'] ) { ?>
				<?php if ( isset( $pro_plugin_is_activated ) && true === $pro_plugin_is_activated ) { ?>
					<script type="text/javascript">
						window.setTimeout( function() {
						    window.location.href = 'admin.php?page=facebook-button-pro.php';
						}, 5000 );
					</script>				
					<p><?php _e( "Congratulations! The PRO version of the plugin is successfully download and activated.", 'facebook' ); ?></p>
					<p>
						<?php _e( "Please, go to", 'facebook' ); ?> <a href="admin.php?page=facebook-button-pro.php"><?php _e( 'the setting page', 'facebook' ); ?></a> 
						(<?php _e( "You will be redirected automatically in 5 seconds.", 'facebook' ); ?>)
					</p>
				<?php } else { ?>
					<form method="post" action="admin.php?page=facebook-button-plugin.php&amp;action=go_pro">
						<p>
							<?php _e( 'You can download and activate', 'facebook' ); ?> 
							<a href="http://bestwebsoft.com/plugin/facebook-like-button-pro/?k=427287ceae749cbd015b4bba6041c4b8&pn=78&v=<?php echo $fcbkbttn_plugin_info["Version"]; ?>&wp_v=<?php echo $wp_version; ?>" target="_blank" title="Facebook Like Button Pro">PRO</a> 
							<?php _e( 'version of this plugin by entering Your license key.', 'facebook' ); ?><br />
							<span style="color: #888888;font-size: 10px;">
								<?php _e( 'You can find your license key on your personal page Client area, by clicking on the link', 'facebook' ); ?> 
								<a href="http://bestwebsoft.com/wp-login.php">http://bestwebsoft.com/wp-login.php</a> 
								<?php _e( '(your username is the email you specify when purchasing the product).', 'facebook' ); ?>
							</span>
						</p>
						<?php if ( isset( $bstwbsftwppdtplgns_options['go_pro']['facebook-button-pro/facebook-button-pro.php']['count'] ) &&
							'5' < $bstwbsftwppdtplgns_options['go_pro']['facebook-button-pro/facebook-button-pro.php']['count'] &&
							$bstwbsftwppdtplgns_options['go_pro']['facebook-button-pro/facebook-button-pro.php']['time'] < ( time() + ( 24 * 60 * 60 ) ) ) { ?>
							<p>
								<input disabled="disabled" type="text" name="bws_license_key" value="<?php echo $bws_license_key; ?>" />
								<input disabled="disabled" type="submit" class="button-primary" value="<?php _e( 'Go!', 'facebook' ); ?>" />
							</p>
							<p>
								<?php _e( "Unfortunately, you have exceeded the number of available tries per day. Please, upload the plugin manually.", 'facebook' ); ?>
							</p>
						<?php } else { ?>
							<p>
								<input type="text" name="bws_license_key" value="<?php echo $bws_license_key; ?>" />
								<input type="hidden" name="bws_license_plugin" value="facebook-button-pro/facebook-button-pro.php" />
								<input type="hidden" name="bws_license_submit" value="submit" />
								<input type="submit" class="button-primary" value="<?php _e( 'Go!', 'facebook' ); ?>" />
								<?php wp_nonce_field( plugin_basename(__FILE__), 'bws_license_nonce_name' ); ?>
							</p>
						<?php } ?>
					</form>
				<?php }
			} ?>
		</div>
	<?php }
}

/* Function reacts to changes type of picture (Standard or Custom) and generates link to image, link transferred to array 'fcbk_bttn_plgn_options' */
if ( ! function_exists( 'fcbkbttn_update_option' ) ) {
	function fcbkbttn_update_option() {
		global $fcbkbttn_options;
		if ( 'standart' == $fcbkbttn_options['display_option'] ) {
			$fb_img_link = plugins_url( 'images/standart-facebook-ico.png', __FILE__ );
		} else if ( 'custom' == $fcbkbttn_options['display_option'] ) {
			$upload_dir = wp_upload_dir();
			$fb_img_link = $upload_dir['baseurl'] . '/facebook-image/facebook-ico' . $fcbkbttn_options['count_icon'] . '.' . $fcbkbttn_options['extention'];
		}
		$fcbkbttn_options['fb_img_link'] = $fb_img_link ;
		update_option( 'fcbk_bttn_plgn_options', $fcbkbttn_options );
	}
}

/* Function taking from array 'fcbk_bttn_plgn_options' necessary information to create Facebook Button and reacting to your choise in plugin menu - points where it appears. */
if ( ! function_exists( 'fcbkbttn_display_button' ) ) {
	function fcbkbttn_display_button( $content ) {
		global $post, $fcbkbttn_options;
		/* Query the database to receive array 'fcbk_bttn_plgn_options' and receiving necessary information to create button */
		$fcbkbttn_where	=	$fcbkbttn_options['where'];
		$permalink_post	=	get_permalink( $post->ID );
		/* Button */
		$button			=	'<div class="fcbk_share">';
		$img			=	$fcbkbttn_options['fb_img_link'];
		$url			=	$fcbkbttn_options['link'];
		if ( 1 == $fcbkbttn_options['my_page'] ) {
			$button .=	'<div class="fcbk_button">
							<a href="http://www.facebook.com/' . $url . '"	target="_blank">
								<img src="' . $img . '" alt="Fb-Button" />
							</a>
						</div>';
		}
		if ( 1 == $fcbkbttn_options['like'] ) {
			$button .= '<div class="fcbk_like">';
			if ( 1 == $fcbkbttn_options['html5'] ) {
				$button .=	'<div class="fb-like" data-href="' . $permalink_post . '" data-layout="button_count" data-action="like" data-show-faces="false"';
					if ( 1 == $fcbkbttn_options['share'] )
						$button .= ' data-share="true"></div></div>';
					else
						$button .= ' data-share="false"></div></div>';
			} else {
				$button .= '<fb:like href="' . $permalink_post . '" layout="button_count" width="450" show_faces="false"';
				if ( 1 == $fcbkbttn_options['share'] )
					$button .= ' share="true"></fb:like></div>';
				else
					$button .= ' share="false"></fb:like></div>';
			}
		} else if ( 1 != $fcbkbttn_options['like'] && 1 == $fcbkbttn_options['share'] ) {
			$button .=	'<div class="fb-share-button" data-href="' . $permalink_post . '" data-type="button_count"></div>';
		}		
		$button .= '</div>';
		/* Indication where show Facebook Button depending on selected item in admin page. */
		if ( 'before' == $fcbkbttn_where ) {
			return $button . $content;
		} else if ( 'after' == $fcbkbttn_where ) {
			return $content . $button;
		} else if ( 'beforeandafter' == $fcbkbttn_where ) {
			return $button . $content . $button;
		} else if ( 'shortcode' == $fcbkbttn_where ) {
			return $content;
		} else {
			return $content;
		}
	}
}

/* Function 'fcbk_bttn_plgn_shortcode' are using to create shortcode by Facebook Button. */
if ( ! function_exists( 'fcbkbttn_shortcode' ) ) {
	function fcbkbttn_shortcode( $content ) {
		global $post, $fcbkbttn_options;
		$fcbkbttn_where	=	$fcbkbttn_options['where'];
		$permalink_post	=	get_permalink( $post->ID );
		$button			=	'<div class="fcbk_share">';
		$img			=	$fcbkbttn_options['fb_img_link'];
		$url			=	$fcbkbttn_options['link'];
		if ( 1 == $fcbkbttn_options['my_page'] ) {
			$button .=	'<div class="fcbk_button">
							<a href="http://www.facebook.com/' . $url . '"	target="_blank">
								<img src="' . $img . '" alt="Fb-Button" />
							</a>
						</div>';
		}
		if ( 1 == $fcbkbttn_options['like'] ) {
			$button .=	'<div class="fcbk_like">
							<div id="fb-root"></div>
							<script>(function(d, s, id) {
								var js, fjs = d.getElementsByTagName(s)[0];
								if (d.getElementById(id)) return;
								js = d.createElement(s); js.id = id;
								js.src = "//connect.facebook.net/' . $fcbkbttn_options['locale'] . '/sdk.js#xfbml=1&appId=1443946719181573&version=v2.0";
								fjs.parentNode.insertBefore(js, fjs);
							}(document, "script", "facebook-jssdk"));</script>';
			if ( 1 == $fcbkbttn_options['html5'] ) {
				$button .=	'<div class="fb-like" data-href="' . $permalink_post . '" data-layout="button_count" data-action="like" data-show-faces="false"';
					if ( 1 == $fcbkbttn_options['share'] )
						$button .= ' data-share="true"></div></div>';
					else
						$button .= ' data-share="false"></div></div>';
			} else {
				$button .= '<fb:like href="' . $permalink_post . '" layout="button_count" width="450" show_faces="false"';
				if ( 1 == $fcbkbttn_options['share'] )
					$button .= ' share="true"></fb:like></div>';
				else
					$button .= ' share="false"></fb:like></div>';
			}
		} else if ( 1 != $fcbkbttn_options['like'] && 1 == $fcbkbttn_options['share'] ) {
			$button .=	'<div class="fb-share-button" data-href="' . $permalink_post . '" data-type="button_count"></div>';
		}
		$button .= '</div>';
		return $button;
	}
}

/* Functions adds some right meta for Facebook */
if ( ! function_exists( 'fcbkbttn_meta' ) ) {
	function fcbkbttn_meta() {
		global $fcbkbttn_options;
		if ( 1 == $fcbkbttn_options['like'] ) {
			if ( is_singular() ) {
				$image = '';
				if ( has_post_thumbnail( get_the_ID() ) ) {
					$image = wp_get_attachment_image_src( get_post_thumbnail_id(), 'thumbnail');
					$image = $image[0];
				}
				print "\n" . '<meta property="og:title" content="' . esc_attr( get_the_title() ) . '"/>';
				print "\n" . '<meta property="og:site_name" content="' . esc_attr( get_bloginfo() ) . '"/>';
				if ( ! empty( $image ) ) {
					print "\n" . '<meta property="og:image" content="' . esc_url( $image ) . '"/>';
				}
			}
		}
	}
}

if ( ! function_exists( 'fcbkbttn_footer_script' ) ) {
	function fcbkbttn_footer_script () {
		global $fcbkbttn_options;
		if ( ( 1 == $fcbkbttn_options['like'] || 1 == $fcbkbttn_options['share'] ) && 'shortcode' != $fcbkbttn_options['where'] ) {
			echo '<div id="fb-root"></div>
			<script>(function(d, s, id) {
				var js, fjs = d.getElementsByTagName(s)[0];
				if (d.getElementById(id)) return;
				js = d.createElement(s); js.id = id;
				js.src = "//connect.facebook.net/' . $fcbkbttn_options['locale'] . '/sdk.js#xfbml=1&appId=1443946719181573&version=v2.0";
				fjs.parentNode.insertBefore(js, fjs);
			}(document, "script", "facebook-jssdk"));</script>';
		}
	}
}

/* Function is using to create action links on admin page. */
if ( ! function_exists( 'fcbkbttn_action_links' ) ) {
	function fcbkbttn_action_links( $links, $file ) {
		/* Static so we don't call plugin_basename on every plugin row. */
		static $this_plugin;
		if ( ! $this_plugin )
			$this_plugin = plugin_basename( __FILE__ );
		if ( $file == $this_plugin ) {
			$settings_link = '<a href="admin.php?page=facebook-button-plugin.php">' . __( 'Settings', 'facebook' ) . '</a>';
			array_unshift( $links, $settings_link );
		}
		return $links;
	}
} /* End function fcbkbttn_action_links */

/* Function are using to create other links on admin page. */
if ( ! function_exists ( 'fcbkbttn_links' ) ) {
	function fcbkbttn_links( $links, $file ) {
		$base = plugin_basename( __FILE__ );
		if ( $file == $base ) {
			$links[]	=	'<a href="admin.php?page=facebook-button-plugin.php">' . __( 'Settings', 'facebook' ) . '</a>';
			$links[]	=	'<a href="http://wordpress.org/plugins/facebook-button-plugin/faq/" target="_blank">' . __( 'FAQ', 'facebook' ) . '</a>';
			$links[]	=	'<a href="http://support.bestwebsoft.com">' . __( 'Support', 'facebook' ) . '</a>';
		}
		return $links;
	}
}
/* End function fcbkbttn_links */

if ( ! function_exists( 'fcbkbttn_admin_head' ) ) {
	function fcbkbttn_admin_head() {
		global $fcbkbttn_options;
		if ( ! is_admin() || ( isset( $_GET['page'] ) && "facebook-button-plugin.php" == $_GET['page'] ) ) {
			wp_enqueue_style( 'fcbk_stylesheet', plugins_url( 'css/style.css', __FILE__ ) );
			wp_enqueue_script( 'fcbk_script', plugins_url( 'js/script.js', __FILE__ ), array( 'jquery' ) );
			if ( ( 1 == $fcbkbttn_options['like'] || 1 == $fcbkbttn_options['share'] ) && 'en_US' != $fcbkbttn_options['locale'] )
				wp_enqueue_script( 'fcbk_connect', '//connect.facebook.net/' . $fcbkbttn_options['locale'] . '/all.js#xfbml=1&appId=1443946719181573' );
		}
	}
}

if ( ! function_exists ( 'fcbkbttn_plugin_banner' ) ) {
	function fcbkbttn_plugin_banner() {
		global $hook_suffix;	
		if ( 'plugins.php' == $hook_suffix ) {
			global $fcbkbttn_plugin_info;
			$banner_array = array(
				array( 'lmtttmpts_hide_banner_on_plugin_page', 'limit-attempts/limit-attempts.php', '1.0.2' ),
				array( 'sndr_hide_banner_on_plugin_page', 'sender/sender.php', '0.5' ),
				array( 'srrl_hide_banner_on_plugin_page', 'user-role/user-role.php', '1.4' ),
				array( 'pdtr_hide_banner_on_plugin_page', 'updater/updater.php', '1.12' ),
				array( 'cntctfrmtdb_hide_banner_on_plugin_page', 'contact-form-to-db/contact_form_to_db.php', '1.2' ),
				array( 'cntctfrmmlt_hide_banner_on_plugin_page', 'contact-form-multi/contact-form-multi.php', '1.0.7' ),		
				array( 'gglmps_hide_banner_on_plugin_page', 'bws-google-maps/bws-google-maps.php', '1.2' ),		
				array( 'fcbkbttn_hide_banner_on_plugin_page', 'facebook-button-plugin/facebook-button-plugin.php', '2.29' ),
				array( 'twttr_hide_banner_on_plugin_page', 'twitter-plugin/twitter.php', '2.34' ),
				array( 'pdfprnt_hide_banner_on_plugin_page', 'pdf-print/pdf-print.php', '1.7.1' ),
				array( 'gglplsn_hide_banner_on_plugin_page', 'google-one/google-plus-one.php', '1.1.4' ),
				array( 'gglstmp_hide_banner_on_plugin_page', 'google-sitemap-plugin/google-sitemap-plugin.php', '2.8.4' ),
				array( 'cntctfrmpr_for_ctfrmtdb_hide_banner_on_plugin_page', 'contact-form-pro/contact_form_pro.php', '1.14' ),
				array( 'cntctfrm_for_ctfrmtdb_hide_banner_on_plugin_page', 'contact-form-plugin/contact_form.php', '3.62' ),
				array( 'cntctfrm_hide_banner_on_plugin_page', 'contact-form-plugin/contact_form.php', '3.47' ),	
				array( 'cptch_hide_banner_on_plugin_page', 'captcha/captcha.php', '3.8.4' ),
				array( 'gllr_hide_banner_on_plugin_page', 'gallery-plugin/gallery-plugin.php', '3.9.1' )				
			);

			if ( ! function_exists( 'is_plugin_active_for_network' ) )
				require_once( ABSPATH . '/wp-admin/includes/plugin.php' );

			$active_plugins = get_option( 'active_plugins' );			
			$all_plugins = get_plugins();
			$this_banner = 'fcbkbttn_hide_banner_on_plugin_page';
			foreach ( $banner_array as $key => $value ) {
				if ( $this_banner == $value[0] ) {
					global $wp_version, $bstwbsftwppdtplgns_cookie_add;
					if ( ! isset( $bstwbsftwppdtplgns_cookie_add ) ) {
						echo '<script type="text/javascript" src="' . plugins_url( 'js/c_o_o_k_i_e.js', __FILE__ ) . '"></script>';
						$bstwbsftwppdtplgns_cookie_add = true;
					} ?>
					<script type="text/javascript">		
						(function($) {
							$(document).ready( function() {		
								var hide_message = $.cookie( "fcbkbttn_hide_banner_on_plugin_page" );
								if ( hide_message == "true") {
									$( ".fcbkbttn_message" ).css( "display", "none" );
								} else {
									$( ".fcbkbttn_message" ).css( "display", "block" );
								};
								$( ".fcbkbttn_close_icon" ).click( function() {
									$( ".fcbkbttn_message" ).css( "display", "none" );
									$.cookie( "fcbkbttn_hide_banner_on_plugin_page", "true", { expires: 32 } );
								});	
							});
						})(jQuery);				
					</script>
					<div class="updated" style="padding: 0; margin: 0; border: none; background: none;">					                      
						<div class="fcbkbttn_message bws_banner_on_plugin_page" style="display: none;">
							<img class="fcbkbttn_close_icon close_icon" title="" src="<?php echo plugins_url( 'images/close_banner.png', __FILE__ ); ?>" alt=""/>
							<div class="button_div">
								<a class="button" target="_blank" href="http://bestwebsoft.com/plugin/facebook-like-button-pro/?k=45862a4b3cd7a03768666310fbdb19db&pn=78&v=<?php echo $fcbkbttn_plugin_info["Version"]; ?>&wp_v=<?php echo $wp_version; ?>"><?php _e( "Learn More", 'facebook' ); ?></a>				
							</div>
							<div class="text">
								<?php _e( "It's time to upgrade your <strong>Facebook Like Button</strong> to <strong>PRO</strong> version", 'facebook' ); ?>!<br />
								<span><?php _e( 'Extend standard plugin functionality with new great options', 'facebook' ); ?>.</span>
							</div> 					
							<div class="icon">
								<img title="" src="<?php echo plugins_url( 'images/banner.png', __FILE__ ); ?>" alt=""/>	
							</div>
						</div>  
					</div>
					<?php break;
				}
				if ( isset( $all_plugins[ $value[1] ] ) && $all_plugins[ $value[1] ]["Version"] >= $value[2] && ( 0 < count( preg_grep( '/' . str_replace( '/', '\/', $value[1] ) . '/', $active_plugins ) ) || is_plugin_active_for_network( $value[1] ) ) && ! isset( $_COOKIE[ $value[0] ] ) ) {
					break;
				}
			}    
		}
	}
}

/* Function for delete options */
if ( ! function_exists( 'fcbkbttn_delete_options' ) ) {
	function fcbkbttn_delete_options() {
		if ( ! function_exists( 'get_plugins' ) )
			require_once( ABSPATH . 'wp-admin/includes/plugin.php' );
		$all_plugins = get_plugins();
		if ( ! array_key_exists( 'facebook-button-pro/facebook-button-pro.php', $all_plugins ) ) {
			/* delete custom images if no PRO version */
			$upload_dir = wp_upload_dir();
			$fcbkbttn_cstm_mg_folder = $upload_dir['basedir'] . '/facebook-image/';
			if ( is_dir( $fcbkbttn_cstm_mg_folder ) ) {
				$fcbkbttn_cstm_mg_files = scandir( $fcbkbttn_cstm_mg_folder );
				foreach ( $fcbkbttn_cstm_mg_files as $value ) {
					@unlink ( $fcbkbttn_cstm_mg_folder . $value );
				}
				@rmdir( $fcbkbttn_cstm_mg_folder );
			}
		}
		delete_option( 'fcbk_bttn_plgn_options' );
		delete_site_option( 'fcbk_bttn_plgn_options' );
	}
}

/* Calling a function add administrative menu. */
add_action( 'admin_menu', 'fcbkbttn_add_pages' );
/* Initialization */
add_action( 'init', 'fcbkbttn_init' );
add_action( 'admin_init', 'fcbkbttn_admin_init' );
/* Adding stylesheets */
add_action( 'wp_enqueue_scripts', 'fcbkbttn_admin_head' );
add_action( 'admin_enqueue_scripts', 'fcbkbttn_admin_head' );
/* Adding front-end stylesheets */
add_action( 'wp_head', 'fcbkbttn_meta' );
add_action( 'wp_footer', 'fcbkbttn_footer_script' );
/* Add shortcode and plugin buttons */
add_shortcode( 'fb_button', 'fcbkbttn_shortcode' );
add_filter( 'the_content', 'fcbkbttn_display_button' );
/* Additional links on the plugin page */
add_filter( 'plugin_action_links', 'fcbkbttn_action_links', 10, 2 );
add_filter( 'plugin_row_meta', 'fcbkbttn_links', 10, 2 );
/* Adding banner */
add_action( 'admin_notices', 'fcbkbttn_plugin_banner' );
/* Plugin uninstall function */
register_uninstall_hook( __FILE__, 'fcbkbttn_delete_options' );
?>