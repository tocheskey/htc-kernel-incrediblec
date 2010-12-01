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
const char *yaffs_checkptrw_c_version =
	"$Id$";


#include "yaffs_checkptrw.h"
#include "yaffs_getblockinfo.h"

static int yaffs_CheckpointSpaceOk(yaffs_Device *dev)
{
	int blocksAvailable = dev->nErasedBlocks - dev->nReservedBlocks;
=======
#include "yaffs_checkptrw.h"
#include "yaffs_getblockinfo.h"

static int yaffs2_CheckpointSpaceOk(yaffs_Device *dev)
{
	int blocksAvailable = dev->nErasedBlocks - dev->param.nReservedBlocks;
>>>>>>> origin/incrediblec-2.6.32

	T(YAFFS_TRACE_CHECKPOINT,
		(TSTR("checkpt blocks available = %d" TENDSTR),
		blocksAvailable));

	return (blocksAvailable <= 0) ? 0 : 1;
}


<<<<<<< HEAD
static int yaffs_CheckpointErase(yaffs_Device *dev)
{
	int i;

	if (!dev->eraseBlockInNAND)
=======
static int yaffs2_CheckpointErase(yaffs_Device *dev)
{
	int i;

	if (!dev->param.eraseBlockInNAND)
>>>>>>> origin/incrediblec-2.6.32
		return 0;
	T(YAFFS_TRACE_CHECKPOINT, (TSTR("checking blocks %d to %d"TENDSTR),
		dev->internalStartBlock, dev->internalEndBlock));

	for (i = dev->internalStartBlock; i <= dev->internalEndBlock; i++) {
		yaffs_BlockInfo *bi = yaffs_GetBlockInfo(dev, i);
		if (bi->blockState == YAFFS_BLOCK_STATE_CHECKPOINT) {
			T(YAFFS_TRACE_CHECKPOINT, (TSTR("erasing checkpt block %d"TENDSTR), i));

			dev->nBlockErasures++;

<<<<<<< HEAD
			if (dev->eraseBlockInNAND(dev, i - dev->blockOffset /* realign */)) {
				bi->blockState = YAFFS_BLOCK_STATE_EMPTY;
				dev->nErasedBlocks++;
				dev->nFreeChunks += dev->nChunksPerBlock;
			} else {
				dev->markNANDBlockBad(dev, i);
=======
			if (dev->param.eraseBlockInNAND(dev, i - dev->blockOffset /* realign */)) {
				bi->blockState = YAFFS_BLOCK_STATE_EMPTY;
				dev->nErasedBlocks++;
				dev->nFreeChunks += dev->param.nChunksPerBlock;
			} else {
				dev->param.markNANDBlockBad(dev, i);
>>>>>>> origin/incrediblec-2.6.32
				bi->blockState = YAFFS_BLOCK_STATE_DEAD;
			}
		}
	}

	dev->blocksInCheckpoint = 0;

	return 1;
}


<<<<<<< HEAD
static void yaffs_CheckpointFindNextErasedBlock(yaffs_Device *dev)
{
	int  i;
	int blocksAvailable = dev->nErasedBlocks - dev->nReservedBlocks;
	T(YAFFS_TRACE_CHECKPOINT,
		(TSTR("allocating checkpt block: erased %d reserved %d avail %d next %d "TENDSTR),
		dev->nErasedBlocks, dev->nReservedBlocks, blocksAvailable, dev->checkpointNextBlock));
=======
static void yaffs2_CheckpointFindNextErasedBlock(yaffs_Device *dev)
{
	int  i;
	int blocksAvailable = dev->nErasedBlocks - dev->param.nReservedBlocks;
	T(YAFFS_TRACE_CHECKPOINT,
		(TSTR("allocating checkpt block: erased %d reserved %d avail %d next %d "TENDSTR),
		dev->nErasedBlocks, dev->param.nReservedBlocks, blocksAvailable, dev->checkpointNextBlock));
>>>>>>> origin/incrediblec-2.6.32

	if (dev->checkpointNextBlock >= 0 &&
			dev->checkpointNextBlock <= dev->internalEndBlock &&
			blocksAvailable > 0) {

		for (i = dev->checkpointNextBlock; i <= dev->internalEndBlock; i++) {
			yaffs_BlockInfo *bi = yaffs_GetBlockInfo(dev, i);
			if (bi->blockState == YAFFS_BLOCK_STATE_EMPTY) {
				dev->checkpointNextBlock = i + 1;
				dev->checkpointCurrentBlock = i;
				T(YAFFS_TRACE_CHECKPOINT, (TSTR("allocating checkpt block %d"TENDSTR), i));
				return;
			}
		}
	}
	T(YAFFS_TRACE_CHECKPOINT, (TSTR("out of checkpt blocks"TENDSTR)));

	dev->checkpointNextBlock = -1;
	dev->checkpointCurrentBlock = -1;
}

<<<<<<< HEAD
static void yaffs_CheckpointFindNextCheckpointBlock(yaffs_Device *dev)
=======
static void yaffs2_CheckpointFindNextCheckpointBlock(yaffs_Device *dev)
>>>>>>> origin/incrediblec-2.6.32
{
	int  i;
	yaffs_ExtendedTags tags;

	T(YAFFS_TRACE_CHECKPOINT, (TSTR("find next checkpt block: start:  blocks %d next %d" TENDSTR),
		dev->blocksInCheckpoint, dev->checkpointNextBlock));

	if (dev->blocksInCheckpoint < dev->checkpointMaxBlocks)
		for (i = dev->checkpointNextBlock; i <= dev->internalEndBlock; i++) {
<<<<<<< HEAD
			int chunk = i * dev->nChunksPerBlock;
			int realignedChunk = chunk - dev->chunkOffset;

			dev->readChunkWithTagsFromNAND(dev, realignedChunk,
=======
			int chunk = i * dev->param.nChunksPerBlock;
			int realignedChunk = chunk - dev->chunkOffset;

			dev->param.readChunkWithTagsFromNAND(dev, realignedChunk,
>>>>>>> origin/incrediblec-2.6.32
					NULL, &tags);
			T(YAFFS_TRACE_CHECKPOINT, (TSTR("find next checkpt block: search: block %d oid %d seq %d eccr %d" TENDSTR),
				i, tags.objectId, tags.sequenceNumber, tags.eccResult));

			if (tags.sequenceNumber == YAFFS_SEQUENCE_CHECKPOINT_DATA) {
				/* Right kind of block */
				dev->checkpointNextBlock = tags.objectId;
				dev->checkpointCurrentBlock = i;
				dev->checkpointBlockList[dev->blocksInCheckpoint] = i;
				dev->blocksInCheckpoint++;
				T(YAFFS_TRACE_CHECKPOINT, (TSTR("found checkpt block %d"TENDSTR), i));
				return;
			}
		}

	T(YAFFS_TRACE_CHECKPOINT, (TSTR("found no more checkpt blocks"TENDSTR)));

	dev->checkpointNextBlock = -1;
	dev->checkpointCurrentBlock = -1;
}


<<<<<<< HEAD
int yaffs_CheckpointOpen(yaffs_Device *dev, int forWriting)
=======
int yaffs2_CheckpointOpen(yaffs_Device *dev, int forWriting)
>>>>>>> origin/incrediblec-2.6.32
{


	dev->checkpointOpenForWrite = forWriting;

	/* Got the functions we need? */
<<<<<<< HEAD
	if (!dev->writeChunkWithTagsToNAND ||
			!dev->readChunkWithTagsFromNAND ||
			!dev->eraseBlockInNAND ||
			!dev->markNANDBlockBad)
		return 0;

	if (forWriting && !yaffs_CheckpointSpaceOk(dev))
		return 0;

	if (!dev->checkpointBuffer)
		dev->checkpointBuffer = YMALLOC_DMA(dev->totalBytesPerChunk);
=======
	if (!dev->param.writeChunkWithTagsToNAND ||
		!dev->param.readChunkWithTagsFromNAND ||
		!dev->param.eraseBlockInNAND ||
		!dev->param.markNANDBlockBad)
		return 0;

	if (forWriting && !yaffs2_CheckpointSpaceOk(dev))
		return 0;

	if (!dev->checkpointBuffer)
		dev->checkpointBuffer = YMALLOC_DMA(dev->param.totalBytesPerChunk);
>>>>>>> origin/incrediblec-2.6.32
	if (!dev->checkpointBuffer)
		return 0;


	dev->checkpointPageSequence = 0;
	dev->checkpointByteCount = 0;
	dev->checkpointSum = 0;
	dev->checkpointXor = 0;
	dev->checkpointCurrentBlock = -1;
	dev->checkpointCurrentChunk = -1;
	dev->checkpointNextBlock = dev->internalStartBlock;

	/* Erase all the blocks in the checkpoint area */
	if (forWriting) {
		memset(dev->checkpointBuffer, 0, dev->nDataBytesPerChunk);
		dev->checkpointByteOffset = 0;
<<<<<<< HEAD
		return yaffs_CheckpointErase(dev);
=======
		return yaffs2_CheckpointErase(dev);
>>>>>>> origin/incrediblec-2.6.32
	} else {
		int i;
		/* Set to a value that will kick off a read */
		dev->checkpointByteOffset = dev->nDataBytesPerChunk;
		/* A checkpoint block list of 1 checkpoint block per 16 block is (hopefully)
		 * going to be way more than we need */
		dev->blocksInCheckpoint = 0;
		dev->checkpointMaxBlocks = (dev->internalEndBlock - dev->internalStartBlock)/16 + 2;
		dev->checkpointBlockList = YMALLOC(sizeof(int) * dev->checkpointMaxBlocks);
		if(!dev->checkpointBlockList)
			return 0;

		for (i = 0; i < dev->checkpointMaxBlocks; i++)
			dev->checkpointBlockList[i] = -1;
	}

	return 1;
}

<<<<<<< HEAD
int yaffs_GetCheckpointSum(yaffs_Device *dev, __u32 *sum)
=======
int yaffs2_GetCheckpointSum(yaffs_Device *dev, __u32 *sum)
>>>>>>> origin/incrediblec-2.6.32
{
	__u32 compositeSum;
	compositeSum =  (dev->checkpointSum << 8) | (dev->checkpointXor & 0xFF);
	*sum = compositeSum;
	return 1;
}

<<<<<<< HEAD
static int yaffs_CheckpointFlushBuffer(yaffs_Device *dev)
=======
static int yaffs2_CheckpointFlushBuffer(yaffs_Device *dev)
>>>>>>> origin/incrediblec-2.6.32
{
	int chunk;
	int realignedChunk;

	yaffs_ExtendedTags tags;

	if (dev->checkpointCurrentBlock < 0) {
<<<<<<< HEAD
		yaffs_CheckpointFindNextErasedBlock(dev);
=======
		yaffs2_CheckpointFindNextErasedBlock(dev);
>>>>>>> origin/incrediblec-2.6.32
		dev->checkpointCurrentChunk = 0;
	}

	if (dev->checkpointCurrentBlock < 0)
		return 0;

	tags.chunkDeleted = 0;
	tags.objectId = dev->checkpointNextBlock; /* Hint to next place to look */
	tags.chunkId = dev->checkpointPageSequence + 1;
	tags.sequenceNumber =  YAFFS_SEQUENCE_CHECKPOINT_DATA;
	tags.byteCount = dev->nDataBytesPerChunk;
	if (dev->checkpointCurrentChunk == 0) {
		/* First chunk we write for the block? Set block state to
		   checkpoint */
		yaffs_BlockInfo *bi = yaffs_GetBlockInfo(dev, dev->checkpointCurrentBlock);
		bi->blockState = YAFFS_BLOCK_STATE_CHECKPOINT;
		dev->blocksInCheckpoint++;
	}

<<<<<<< HEAD
	chunk = dev->checkpointCurrentBlock * dev->nChunksPerBlock + dev->checkpointCurrentChunk;
=======
	chunk = dev->checkpointCurrentBlock * dev->param.nChunksPerBlock + dev->checkpointCurrentChunk;
>>>>>>> origin/incrediblec-2.6.32


	T(YAFFS_TRACE_CHECKPOINT, (TSTR("checkpoint wite buffer nand %d(%d:%d) objid %d chId %d" TENDSTR),
		chunk, dev->checkpointCurrentBlock, dev->checkpointCurrentChunk, tags.objectId, tags.chunkId));

	realignedChunk = chunk - dev->chunkOffset;

	dev->nPageWrites++;

<<<<<<< HEAD
	dev->writeChunkWithTagsToNAND(dev, realignedChunk,
=======
	dev->param.writeChunkWithTagsToNAND(dev, realignedChunk,
>>>>>>> origin/incrediblec-2.6.32
			dev->checkpointBuffer, &tags);
	dev->checkpointByteOffset = 0;
	dev->checkpointPageSequence++;
	dev->checkpointCurrentChunk++;
<<<<<<< HEAD
	if (dev->checkpointCurrentChunk >= dev->nChunksPerBlock) {
=======
	if (dev->checkpointCurrentChunk >= dev->param.nChunksPerBlock) {
>>>>>>> origin/incrediblec-2.6.32
		dev->checkpointCurrentChunk = 0;
		dev->checkpointCurrentBlock = -1;
	}
	memset(dev->checkpointBuffer, 0, dev->nDataBytesPerChunk);

	return 1;
}


<<<<<<< HEAD
int yaffs_CheckpointWrite(yaffs_Device *dev, const void *data, int nBytes)
=======
int yaffs2_CheckpointWrite(yaffs_Device *dev, const void *data, int nBytes)
>>>>>>> origin/incrediblec-2.6.32
{
	int i = 0;
	int ok = 1;


	__u8 * dataBytes = (__u8 *)data;



	if (!dev->checkpointBuffer)
		return 0;

	if (!dev->checkpointOpenForWrite)
		return -1;

	while (i < nBytes && ok) {
		dev->checkpointBuffer[dev->checkpointByteOffset] = *dataBytes;
		dev->checkpointSum += *dataBytes;
		dev->checkpointXor ^= *dataBytes;

		dev->checkpointByteOffset++;
		i++;
		dataBytes++;
		dev->checkpointByteCount++;


		if (dev->checkpointByteOffset < 0 ||
		   dev->checkpointByteOffset >= dev->nDataBytesPerChunk)
<<<<<<< HEAD
			ok = yaffs_CheckpointFlushBuffer(dev);
=======
			ok = yaffs2_CheckpointFlushBuffer(dev);
>>>>>>> origin/incrediblec-2.6.32
	}

	return i;
}

<<<<<<< HEAD
int yaffs_CheckpointRead(yaffs_Device *dev, void *data, int nBytes)
=======
int yaffs2_CheckpointRead(yaffs_Device *dev, void *data, int nBytes)
>>>>>>> origin/incrediblec-2.6.32
{
	int i = 0;
	int ok = 1;
	yaffs_ExtendedTags tags;


	int chunk;
	int realignedChunk;

	__u8 *dataBytes = (__u8 *)data;

	if (!dev->checkpointBuffer)
		return 0;

	if (dev->checkpointOpenForWrite)
		return -1;

	while (i < nBytes && ok) {


		if (dev->checkpointByteOffset < 0 ||
			dev->checkpointByteOffset >= dev->nDataBytesPerChunk) {

			if (dev->checkpointCurrentBlock < 0) {
<<<<<<< HEAD
				yaffs_CheckpointFindNextCheckpointBlock(dev);
=======
				yaffs2_CheckpointFindNextCheckpointBlock(dev);
>>>>>>> origin/incrediblec-2.6.32
				dev->checkpointCurrentChunk = 0;
			}

			if (dev->checkpointCurrentBlock < 0)
				ok = 0;
			else {
				chunk = dev->checkpointCurrentBlock *
<<<<<<< HEAD
					dev->nChunksPerBlock +
=======
					dev->param.nChunksPerBlock +
>>>>>>> origin/incrediblec-2.6.32
					dev->checkpointCurrentChunk;

				realignedChunk = chunk - dev->chunkOffset;
				
				dev->nPageReads++;

				/* read in the next chunk */
				/* printf("read checkpoint page %d\n",dev->checkpointPage); */
<<<<<<< HEAD
				dev->readChunkWithTagsFromNAND(dev,
=======
				dev->param.readChunkWithTagsFromNAND(dev,
>>>>>>> origin/incrediblec-2.6.32
						realignedChunk,
						dev->checkpointBuffer,
						&tags);

				if (tags.chunkId != (dev->checkpointPageSequence + 1) ||
					tags.eccResult > YAFFS_ECC_RESULT_FIXED ||
					tags.sequenceNumber != YAFFS_SEQUENCE_CHECKPOINT_DATA)
					ok = 0;

				dev->checkpointByteOffset = 0;
				dev->checkpointPageSequence++;
				dev->checkpointCurrentChunk++;

<<<<<<< HEAD
				if (dev->checkpointCurrentChunk >= dev->nChunksPerBlock)
=======
				if (dev->checkpointCurrentChunk >= dev->param.nChunksPerBlock)
>>>>>>> origin/incrediblec-2.6.32
					dev->checkpointCurrentBlock = -1;
			}
		}

		if (ok) {
			*dataBytes = dev->checkpointBuffer[dev->checkpointByteOffset];
			dev->checkpointSum += *dataBytes;
			dev->checkpointXor ^= *dataBytes;
			dev->checkpointByteOffset++;
			i++;
			dataBytes++;
			dev->checkpointByteCount++;
		}
	}

	return 	i;
}

<<<<<<< HEAD
int yaffs_CheckpointClose(yaffs_Device *dev)
=======
int yaffs2_CheckpointClose(yaffs_Device *dev)
>>>>>>> origin/incrediblec-2.6.32
{

	if (dev->checkpointOpenForWrite) {
		if (dev->checkpointByteOffset != 0)
<<<<<<< HEAD
			yaffs_CheckpointFlushBuffer(dev);
=======
			yaffs2_CheckpointFlushBuffer(dev);
>>>>>>> origin/incrediblec-2.6.32
	} else if(dev->checkpointBlockList){
		int i;
		for (i = 0; i < dev->blocksInCheckpoint && dev->checkpointBlockList[i] >= 0; i++) {
			int blk = dev->checkpointBlockList[i];
			yaffs_BlockInfo *bi = NULL;
			if( dev->internalStartBlock <= blk && blk <= dev->internalEndBlock)
				bi = yaffs_GetBlockInfo(dev, blk);
			if (bi && bi->blockState == YAFFS_BLOCK_STATE_EMPTY)
				bi->blockState = YAFFS_BLOCK_STATE_CHECKPOINT;
			else {
				/* Todo this looks odd... */
			}
		}
		YFREE(dev->checkpointBlockList);
		dev->checkpointBlockList = NULL;
	}

<<<<<<< HEAD
	dev->nFreeChunks -= dev->blocksInCheckpoint * dev->nChunksPerBlock;
=======
	dev->nFreeChunks -= dev->blocksInCheckpoint * dev->param.nChunksPerBlock;
>>>>>>> origin/incrediblec-2.6.32
	dev->nErasedBlocks -= dev->blocksInCheckpoint;


	T(YAFFS_TRACE_CHECKPOINT, (TSTR("checkpoint byte count %d" TENDSTR),
			dev->checkpointByteCount));

	if (dev->checkpointBuffer) {
		/* free the buffer */
		YFREE(dev->checkpointBuffer);
		dev->checkpointBuffer = NULL;
		return 1;
	} else
		return 0;
}

<<<<<<< HEAD
int yaffs_CheckpointInvalidateStream(yaffs_Device *dev)
=======
int yaffs2_CheckpointInvalidateStream(yaffs_Device *dev)
>>>>>>> origin/incrediblec-2.6.32
{
	/* Erase the checkpoint data */

	T(YAFFS_TRACE_CHECKPOINT, (TSTR("checkpoint invalidate of %d blocks"TENDSTR),
		dev->blocksInCheckpoint));

<<<<<<< HEAD
	return yaffs_CheckpointErase(dev);
}
=======
	return yaffs2_CheckpointErase(dev);
}



>>>>>>> origin/incrediblec-2.6.32
