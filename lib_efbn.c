/*!
	@file   lib_efbn.c
	@brief  <brief description here>
	@t.odo	-
	---------------------------------------------------------------------------
	MIT License
	Copyright (c) 2022 Energica Motor Company (Dan.R / Gio.M)
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/
/******************************************************************************
* Preprocessor Definitions & Macros
******************************************************************************/

/******************************************************************************
* Includes
******************************************************************************/
#include "lib_efbn.h"

//#ifdef LIB_EFBN_ENABLED

/******************************************************************************
* Enumerations, structures & Variables
******************************************************************************/

/******************************************************************************
* Declaration | Static Functions
******************************************************************************/

/******************************************************************************
* Definition  | Static Functions
******************************************************************************/

/******************************************************************************
* Definition  | Public Functions
******************************************************************************/
i_status efbn_init(efbn_t* h_efbn, efbn_entry_t *entries, size_t entries_cnt)
{
	if (h_efbn == NULL) return I_ERROR;

	h_efbn->entries = entries;
	h_efbn->entries_cnt = entries_cnt;

	return I_OK;
}


i_status efbn_exists_by_id(efbn_t* h, uint32_t id)
{
	i_status r = I_NOTEXISTS;

	for(register uint32_t i = 0; i < h->entries_cnt; i++)
	{
		if(h->entries[i].id == id)
			r = I_EXISTS;
	}
	return r;
}

i_status efbn_exists_by_address(efbn_t* h, uint32_t address)
{
	i_status r = I_NOTEXISTS;

	for(register uint32_t i = 0; i < h->entries_cnt; i++)
	{
		if((uint32_t)h->entries[i].func == address)
			r = I_EXISTS;
	}
	return r;
}

i_status efbn_execute(efbn_t* h, uint32_t id, void* data, uint32_t data_sz)
{
	for(register uint32_t i = 0; i < h->entries_cnt; i++)
	{
		if(h->entries[i].id == id)
		{
			h->entries[i].func(data,data_sz);
			return I_OK;
		}
	}
	return I_INVALID;
}

/******************************************************************************
* EOF - NO CODE AFTER THIS LINE
******************************************************************************/
//#endif