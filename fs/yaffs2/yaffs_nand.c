/*
 * YAFFS: Yet Another Flash File System. A NAND-flash specific file system.
 *
<<<<<<< HEAD
 * Copyright (C) 2002-2007 Aleph One Ltd.
=======
 * Copyright (C) 2002-2010 Aleph One Ltd.
>>>>>>> origin/incrediblec-2.6.32
 *   for Toby Churchill Ltd and Brightstar Engineering
 *
 * Created by Charles Manning <charles@aleph1.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

<<<<<<< HEAD
const char *yaffs_nand_c_version =
	"$Id$";

=======
>>>>>>> origin/incrediblec-2.6.32
#include "yaffs_nand.h"
#include "yaffs_tagscompat.h"
#include "yaffs_tagsvalidity.h"

#include "yaffs_getblockinfo.h"

int yaffs_ReadChunkWithTagsFromNAND(yaffs_Device *dev, int chunkInNAND,
					   __u8 *buffer,
					   yaffs_ExtendedTags *tags)
{
	int result;
	yaffs_ExtendedTags localTags;

	int realignedChunkInNAND = chunkInNAND - dev->chunkOffset;

	dev->nPageReads++;

	/* If there are no tags provided, use local tags to get prioritised gc working */
	if (!tags)
		tags = &localTags;

<<<<<<< HEAD
	if (dev->readChunkWithTagsFromNAND)
		result = dev->readChunkWithTagsFromNAND(dev, realignedChunkInNAND, buffer,
=======
	if (dev->param.readChunkWithTagsFromNAND)
		result = dev->param.readChunkWithTagsFromNAND(dev, realignedChunkInNAND, buffer,
>>>>>>> origin/incrediblec-2.6.32
						      tags);
	else
		result = yaffs_TagsCompatabilityReadChunkWithTagsFromNAND(dev,
									realignedChunkInNAND,
									buffer,
									tags);
	if (tags &&
	   tags->eccResult > YAFFS_ECC_RESULT_NO_ERROR) {

<<<<<<< HEAD
		yaffs_BlockInfo *bi = yaffs_GetBlockInfo(dev, chunkInNAND/dev->nChunksPerBlock);
=======
		yaffs_BlockInfo *bi;
		bi = yaffs_GetBlockInfo(dev, chunkInNAND/dev->param.nChunksPerBlock);
>>>>>>> origin/incrediblec-2.6.32
		yaffs_HandleChunkError(dev, bi);
	}

	return result;
}

int yaffs_WriteChunkWithTagsToNAND(yaffs_Device *dev,
						   int chunkInNAND,
						   const __u8 *buffer,
						   yaffs_ExtendedTags *tags)
{

	dev->nPageWrites++;

	chunkInNAND -= dev->chunkOffset;


	if (tags) {
		tags->sequenceNumber = dev->sequenceNumber;
		tags->chunkUsed = 1;
		if (!yaffs_ValidateTags(tags)) {
			T(YAFFS_TRACE_ERROR,
			  (TSTR("Writing uninitialised tags" TENDSTR)));
			YBUG();
		}
		T(YAFFS_TRACE_WRITE,
		  (TSTR("Writing chunk %d tags %d %d" TENDSTR), chunkInNAND,
		   tags->objectId, tags->chunkId));
	} else {
		T(YAFFS_TRACE_ERROR, (TSTR("Writing with no tags" TENDSTR)));
		YBUG();
	}

<<<<<<< HEAD
	if (dev->writeChunkWithTagsToNAND)
		return dev->writeChunkWithTagsToNAND(dev, chunkInNAND, buffer,
=======
	if (dev->param.writeChunkWithTagsToNAND)
		return dev->param.writeChunkWithTagsToNAND(dev, chunkInNAND, buffer,
>>>>>>> origin/incrediblec-2.6.32
						     tags);
	else
		return yaffs_TagsCompatabilityWriteChunkWithTagsToNAND(dev,
								       chunkInNAND,
								       buffer,
								       tags);
}

int yaffs_MarkBlockBad(yaffs_Device *dev, int blockNo)
{
	blockNo -= dev->blockOffset;


<<<<<<< HEAD
	if (dev->markNANDBlockBad)
		return dev->markNANDBlockBad(dev, blockNo);
=======
	if (dev->param.markNANDBlockBad)
		return dev->param.markNANDBlockBad(dev, blockNo);
>>>>>>> origin/incrediblec-2.6.32
	else
		return yaffs_TagsCompatabilityMarkNANDBlockBad(dev, blockNo);
}

int yaffs_QueryInitialBlockState(yaffs_Device *dev,
						 int blockNo,
						 yaffs_BlockState *state,
						 __u32 *sequenceNumber)
{
	blockNo -= dev->blockOffset;

<<<<<<< HEAD
	if (dev->queryNANDBlock)
		return dev->queryNANDBlock(dev, blockNo, state, sequenceNumber);
=======
	if (dev->param.queryNANDBlock)
		return dev->param.queryNANDBlock(dev, blockNo, state, sequenceNumber);
>>>>>>> origin/incrediblec-2.6.32
	else
		return yaffs_TagsCompatabilityQueryNANDBlock(dev, blockNo,
							     state,
							     sequenceNumber);
}


int yaffs_EraseBlockInNAND(struct yaffs_DeviceStruct *dev,
				  int blockInNAND)
{
	int result;

	blockInNAND -= dev->blockOffset;

	dev->nBlockErasures++;

<<<<<<< HEAD
	result = dev->eraseBlockInNAND(dev, blockInNAND);
=======
	result = dev->param.eraseBlockInNAND(dev, blockInNAND);
>>>>>>> origin/incrediblec-2.6.32

	return result;
}

int yaffs_InitialiseNAND(struct yaffs_DeviceStruct *dev)
{
<<<<<<< HEAD
	return dev->initialiseNAND(dev);
=======
	if(dev->param.initialiseNAND)
		return dev->param.initialiseNAND(dev);
	return YAFFS_OK;
>>>>>>> origin/incrediblec-2.6.32
}



