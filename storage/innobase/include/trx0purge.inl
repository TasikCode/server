/*****************************************************************************

Copyright (c) 1996, 2013, Oracle and/or its affiliates. All Rights Reserved.

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; version 2 of the License.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1335 USA

*****************************************************************************/

/**************************************************//**
@file include/trx0purge.ic
Purge old versions

Created 3/26/1996 Heikki Tuuri
*******************************************************/

#include "trx0undo.h"

/********************************************************************//**
Calculates the file address of an undo log header when we have the file
address of its history list node.
@return file address of the log */
UNIV_INLINE
fil_addr_t
trx_purge_get_log_from_hist(
/*========================*/
	fil_addr_t	node_addr)	/*!< in: file address of the history
					list node of the log */
{
	node_addr.boffset -= TRX_UNDO_HISTORY_NODE;

	return(node_addr);
}

/********************************************************************//**
address of its history list node.
@return true if purge_sys_t::limit <= purge_sys_t::iter */
UNIV_INLINE
bool
trx_purge_check_limit(void)
/*=======================*/
{
	/* limit is used to track till what point purge element has been
	processed and so limit <= iter.
	undo_no ordering is enforced only within the same rollback segment.
	If a transaction uses multiple rollback segments then we need to
	consider the rollback segment space id too. */
	return(purge_sys->iter.trx_no > purge_sys->limit.trx_no
	       || (purge_sys->iter.trx_no == purge_sys->limit.trx_no
		   && ((purge_sys->iter.undo_no >= purge_sys->limit.undo_no)
		       || (purge_sys->iter.undo_rseg_space
			   != purge_sys->limit.undo_rseg_space))));
}
