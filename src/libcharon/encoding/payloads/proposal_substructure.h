/*
 * Copyright (C) 2005-2006 Martin Willi
 * Copyright (C) 2005 Jan Hutter
 * Hochschule fuer Technik Rapperswil
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

/**
 * @defgroup proposal_substructure proposal_substructure
 * @{ @ingroup payloads
 */

#ifndef PROPOSAL_SUBSTRUCTURE_H_
#define PROPOSAL_SUBSTRUCTURE_H_

typedef struct proposal_substructure_t proposal_substructure_t;

#include <library.h>
#include <encoding/payloads/payload.h>
#include <encoding/payloads/transform_substructure.h>
#include <config/proposal.h>
#include <utils/linked_list.h>

/**
 * Class representing an IKEv1/IKEv2 proposal substructure.
 */
struct proposal_substructure_t {

	/**
	 * The payload_t interface.
	 */
	payload_t payload_interface;

	/**
	 * Sets the proposal number of current proposal.
	 *
	 * @param id			proposal number to set
	 */
	void (*set_proposal_number) (proposal_substructure_t *this,
								 u_int8_t proposal_number);
	/**
	 * get proposal number of current proposal.
	 *
	 * @return 			proposal number of current proposal substructure.
	 */
	u_int8_t (*get_proposal_number) (proposal_substructure_t *this);

	/**
	 * Sets the protocol id of current proposal.
	 *
	 * @param id		protocol id to set
	 */
	void (*set_protocol_id) (proposal_substructure_t *this,
							 u_int8_t protocol_id);

	/**
	 * get protocol id of current proposal.
	 *
	 * @return 			protocol id of current proposal substructure.
	 */
	u_int8_t (*get_protocol_id) (proposal_substructure_t *this);

	/**
	 * Sets the next_payload field of this substructure
	 *
	 * If this is the last proposal, next payload field is set to 0,
	 * otherwise to 2
	 *
	 * @param is_last	When TRUE, next payload field is set to 0, otherwise to 2
	 */
	void (*set_is_last_proposal) (proposal_substructure_t *this, bool is_last);

	/**
	 * Returns the currently set SPI of this proposal.
	 *
	 * @return 			chunk_t pointing to the value
	 */
	chunk_t (*get_spi) (proposal_substructure_t *this);

	/**
	 * Sets the SPI of the current proposal.
	 *
	 * @warning SPI is getting copied
	 *
	 * @param spi		chunk_t pointing to the value to set
	 */
	void (*set_spi) (proposal_substructure_t *this, chunk_t spi);

	/**
	 * Get a proposal_t from the propsal_substructure_t.
	 *
	 * @return			proposal_t
	 */
	proposal_t * (*get_proposal) (proposal_substructure_t *this);

	/**
	 * Create an enumerator over transform substructures.
	 *
	 * @return			enumerator over transform_substructure_t
	 */
	enumerator_t* (*create_substructure_enumerator)(proposal_substructure_t *this);

	/**
	 * Destroys an proposal_substructure_t object.
	 */
	void (*destroy) (proposal_substructure_t *this);
};

/**
 * Creates an empty proposal_substructure_t object
 *
 * @param type		PROPOSAL_SUBSTRUCTURE or PROPOSAL_SUBSTRUCTURE_V1
 * @return			proposal_substructure_t object
 */
proposal_substructure_t *proposal_substructure_create(payload_type_t type);

/**
 * Creates a proposal_substructure_t from a proposal_t.
 *
 * @param type		PROPOSAL_SUBSTRUCTURE or PROPOSAL_SUBSTRUCTURE_V1
 * @param proposal	proposal to build a substruct out of it
 * @return 			proposal_substructure_t object
 */
proposal_substructure_t *proposal_substructure_create_from_proposal(
									payload_type_t type, proposal_t *proposal);

/**
 * Creates a proposal_substructure_t from a list of proposal_t (IKEv1 only).
 *
 * @param proposal	proposal to build a substruct out of it
 * @return 			IKEv1 proposal_substructure_t PROPOSAL_SUBSTRUCTURE_V1
 */
proposal_substructure_t *proposal_substructure_create_from_proposals(
									linked_list_t *proposals);

#endif /** PROPOSAL_SUBSTRUCTURE_H_ @}*/
