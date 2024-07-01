/*
 * Copyright (c) 2024 NVIDIA CORPORATION & AFFILIATES, ALL RIGHTS RESERVED.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#ifndef DOCA_PLUGIN_H_
#define DOCA_PLUGIN_H_

#include <library.h>
#include <plugins/plugin.h>

typedef struct doca_plugin_t doca_plugin_t;

/**
 * DOCA interface plugin
 */
struct doca_plugin_t {

	/**
	 * implements plugin interface
	 */
	plugin_t plugin;

};

#endif /** DOCA_PLUGIN_H_ @}*/
