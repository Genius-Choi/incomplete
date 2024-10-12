<?php
/*
Plugin Name: Wp-Insert
Plugin URI: http://www.wp-insert.smartlogix.co.in/
Description: WP-INSERT by SMARTLOGIX : The ultimate wordpress plugin (No1 Adsense Plugin for Wordpress)
Version: 2.0.9
Author: Namith Jawahar
Author URI: http://www.smartlogix.co.in/
WP-INSERT by SMARTLOGIX : The ultimate wordpress plugin (No1 Adsense Plugin for Wordpress)
*/

/*  Copyright 2009  NAMITH JAWAHAR  (website : http://www.smartlogix.co.in)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
/*Definitions*/
if(!defined('WP_INSERT_URL'))
	define('WP_INSERT_URL',plugins_url().'/wp-insert');
if(!defined('WP_INSERT_DIR'))
	define('WP_INSERT_DIR',WP_PLUGIN_DIR.'/wp-insert');
if(!defined('WP_INSERT_VERSION'))
	define('WP_INSERT_VERSION', '2.0.8');
/*Includes*/
require_once (dirname(__FILE__).'/includes/includes.php');
?>