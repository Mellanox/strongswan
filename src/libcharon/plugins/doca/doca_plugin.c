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

#include "doca_plugin.h"
#include "doca_plugin_ipsec.h"

#include <utils/debug.h>
#include <daemon.h>

typedef struct private_doca_plugin_t private_doca_plugin_t;

/**
 * private data of DOCA plugin
 */
struct private_doca_plugin_t {

	/**
	 * implements plugin interface
	 */
	doca_plugin_t public;
};

METHOD(plugin_t, get_name, char*,
	private_doca_plugin_t *this)
{
	return "doca";
}

METHOD(plugin_t, get_features, int,
	private_doca_plugin_t *this, plugin_feature_t *features[])
{
	static plugin_feature_t f[] = {
		PLUGIN_CALLBACK(kernel_ipsec_register, doca_plugin_ipsec_create),
			PLUGIN_PROVIDE(CUSTOM, "kernel-ipsec"),
	};
	*features = f;
	return countof(f);
}

METHOD(plugin_t, destroy, void,
	private_doca_plugin_t *this)
{
	free(this);
}

/**
 * see header file
 */
plugin_t *doca_plugin_create()
{
	private_doca_plugin_t *this;

	INIT(this,
		.public = {
			.plugin = {
				.get_name = _get_name,
				.get_features = _get_features,
				.destroy = _destroy,
			},
		},
	);

	return &this->public.plugin;
}
