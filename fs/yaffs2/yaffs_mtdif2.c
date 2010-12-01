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

/* mtd interface for YAFFS2 */

<<<<<<< HEAD
const char *yaffs_mtdif2_c_version =
	"$Id$";

#include "yportenv.h"

=======
#include "yportenv.h"
#include "yaffs_trace.h"
>>>>>>> origin/incrediblec-2.6.32

#include "yaffs_mtdif2.h"

#include "linux/mtd/mtd.h"
#include "linux/types.h"
#include "linux/time.h"

#include "yaffs_packedtags2.h"

<<<<<<< HEAD
=======
#include "yaffs_linux.h"

>>>>>>> origin/incrediblec-2.6.32
/* NB For use with inband tags....
 * We assume that the data buffer is of size totalBytersPerChunk so that we can also
 * use it to load the tags.
 */
int nandmtd2_WriteChunkWithTagsToNAND(yaffs_Device *dev, int chunkInNAND,
				      const __u8 *data,
				      const yaffs_ExtendedTags *tags)
{
<<<<<<< HEAD
	struct mtd_info *mtd = (struct mtd_info *)(dev->genericDevice);
=======
	struct mtd_info *mtd = yaffs_DeviceToMtd(dev);
>>>>>>> origin/incrediblec-2.6.32
#if (MTD_VERSION_CODE > MTD_VERSION(2, 6, 17))
	struct mtd_oob_ops ops;
#else
	size_t dummy;
#endif
	int retval = 0;

	loff_t addr;

	yaffs_PackedTags2 pt;

<<<<<<< HEAD
=======
	int packed_tags_size = dev->param.noTagsECC ? sizeof(pt.t) : sizeof(pt);
	void * packed_tags_ptr = dev->param.noTagsECC ? (void *) &pt.t : (void *)&pt;

>>>>>>> origin/incrediblec-2.6.32
	T(YAFFS_TRACE_MTD,
	  (TSTR
	   ("nandmtd2_WriteChunkWithTagsToNAND chunk %d data %p tags %p"
	    TENDSTR), chunkInNAND, data, tags));

<<<<<<< HEAD
	addr  = ((loff_t) chunkInNAND) * dev->totalBytesPerChunk;
=======

	addr  = ((loff_t) chunkInNAND) * dev->param.totalBytesPerChunk;
>>>>>>> origin/incrediblec-2.6.32

	/* For yaffs2 writing there must be both data and tags.
	 * If we're using inband tags, then the tags are stuffed into
	 * the end of the data buffer.
	 */
	if (!data || !tags)
		BUG();
<<<<<<< HEAD
	else if (dev->inbandTags) {
=======
	else if (dev->param.inbandTags) {
>>>>>>> origin/incrediblec-2.6.32
		yaffs_PackedTags2TagsPart *pt2tp;
		pt2tp = (yaffs_PackedTags2TagsPart *)(data + dev->nDataBytesPerChunk);
		yaffs_PackTags2TagsPart(pt2tp, tags);
	} else
<<<<<<< HEAD
		yaffs_PackTags2(&pt, tags);

#if (LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 17))
	ops.mode = MTD_OOB_AUTO;
	ops.ooblen = (dev->inbandTags) ? 0 : sizeof(pt);
	ops.len = dev->totalBytesPerChunk;
	ops.ooboffs = 0;
	ops.datbuf = (__u8 *)data;
	ops.oobbuf = (dev->inbandTags) ? NULL : (void *)&pt;
	retval = mtd->write_oob(mtd, addr, &ops);

#else
	if (!dev->inbandTags) {
		retval =
		    mtd->write_ecc(mtd, addr, dev->nDataBytesPerChunk,
				   &dummy, data, (__u8 *) &pt, NULL);
	} else {
		retval =
		    mtd->write(mtd, addr, dev->totalBytesPerChunk, &dummy,
=======
		yaffs_PackTags2(&pt, tags, !dev->param.noTagsECC);

#if (LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 17))
	ops.mode = MTD_OOB_AUTO;
	ops.ooblen = (dev->param.inbandTags) ? 0 : packed_tags_size;
	ops.len = dev->param.totalBytesPerChunk;
	ops.ooboffs = 0;
	ops.datbuf = (__u8 *)data;
	ops.oobbuf = (dev->param.inbandTags) ? NULL : packed_tags_ptr;
	retval = mtd->write_oob(mtd, addr, &ops);

#else
	if (!dev->param.inbandTags) {
		retval =
		    mtd->write_ecc(mtd, addr, dev->nDataBytesPerChunk,
				   &dummy, data, (__u8 *) packed_tags_ptr, NULL);
	} else {
		retval =
		    mtd->write(mtd, addr, dev->param.totalBytesPerChunk, &dummy,
>>>>>>> origin/incrediblec-2.6.32
			       data);
	}
#endif

	if (retval == 0)
		return YAFFS_OK;
	else
		return YAFFS_FAIL;
}

int nandmtd2_ReadChunkWithTagsFromNAND(yaffs_Device *dev, int chunkInNAND,
				       __u8 *data, yaffs_ExtendedTags *tags)
{
<<<<<<< HEAD
	struct mtd_info *mtd = (struct mtd_info *)(dev->genericDevice);
=======
	struct mtd_info *mtd = yaffs_DeviceToMtd(dev);
>>>>>>> origin/incrediblec-2.6.32
#if (MTD_VERSION_CODE > MTD_VERSION(2, 6, 17))
	struct mtd_oob_ops ops;
#endif
	size_t dummy;
	int retval = 0;
	int localData = 0;

<<<<<<< HEAD
	loff_t addr = ((loff_t) chunkInNAND) * dev->totalBytesPerChunk;

	yaffs_PackedTags2 pt;

=======
	loff_t addr = ((loff_t) chunkInNAND) * dev->param.totalBytesPerChunk;

	yaffs_PackedTags2 pt;

	int packed_tags_size = dev->param.noTagsECC ? sizeof(pt.t) : sizeof(pt);
	void * packed_tags_ptr = dev->param.noTagsECC ? (void *) &pt.t: (void *)&pt;

>>>>>>> origin/incrediblec-2.6.32
	T(YAFFS_TRACE_MTD,
	  (TSTR
	   ("nandmtd2_ReadChunkWithTagsFromNAND chunk %d data %p tags %p"
	    TENDSTR), chunkInNAND, data, tags));

<<<<<<< HEAD
	if (dev->inbandTags) {
=======
	if (dev->param.inbandTags) {
>>>>>>> origin/incrediblec-2.6.32

		if (!data) {
			localData = 1;
			data = yaffs_GetTempBuffer(dev, __LINE__);
		}


	}


#if (LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 17))
<<<<<<< HEAD
	if (dev->inbandTags || (data && !tags))
		retval = mtd->read(mtd, addr, dev->totalBytesPerChunk,
				&dummy, data);
	else if (tags) {
		ops.mode = MTD_OOB_AUTO;
		ops.ooblen = sizeof(pt);
		ops.len = data ? dev->nDataBytesPerChunk : sizeof(pt);
		ops.ooboffs = 0;
		ops.datbuf = data;
		ops.oobbuf = dev->spareBuffer;
		retval = mtd->read_oob(mtd, addr, &ops);
	}
#else
	if (!dev->inbandTags && data && tags) {
=======
	if (dev->param.inbandTags || (data && !tags))
		retval = mtd->read(mtd, addr, dev->param.totalBytesPerChunk,
				&dummy, data);
	else if (tags) {
		ops.mode = MTD_OOB_AUTO;
		ops.ooblen = packed_tags_size;
		ops.len = data ? dev->nDataBytesPerChunk : packed_tags_size;
		ops.ooboffs = 0;
		ops.datbuf = data;
		ops.oobbuf = yaffs_DeviceToLC(dev)->spareBuffer;
		retval = mtd->read_oob(mtd, addr, &ops);
	}
#else
	if (!dev->param.inbandTags && data && tags) {
>>>>>>> origin/incrediblec-2.6.32

		retval = mtd->read_ecc(mtd, addr, dev->nDataBytesPerChunk,
					  &dummy, data, dev->spareBuffer,
					  NULL);
	} else {
		if (data)
			retval =
			    mtd->read(mtd, addr, dev->nDataBytesPerChunk, &dummy,
				      data);
<<<<<<< HEAD
		if (!dev->inbandTags && tags)
=======
		if (!dev->param.inbandTags && tags)
>>>>>>> origin/incrediblec-2.6.32
			retval =
			    mtd->read_oob(mtd, addr, mtd->oobsize, &dummy,
					  dev->spareBuffer);
	}
#endif


<<<<<<< HEAD
	if (dev->inbandTags) {
=======
	if (dev->param.inbandTags) {
>>>>>>> origin/incrediblec-2.6.32
		if (tags) {
			yaffs_PackedTags2TagsPart *pt2tp;
			pt2tp = (yaffs_PackedTags2TagsPart *)&data[dev->nDataBytesPerChunk];
			yaffs_UnpackTags2TagsPart(tags, pt2tp);
		}
	} else {
		if (tags) {
<<<<<<< HEAD
			memcpy(&pt, dev->spareBuffer, sizeof(pt));
			yaffs_UnpackTags2(tags, &pt);
=======
			memcpy(packed_tags_ptr, yaffs_DeviceToLC(dev)->spareBuffer, packed_tags_size);
			yaffs_UnpackTags2(tags, &pt, !dev->param.noTagsECC);
>>>>>>> origin/incrediblec-2.6.32
		}
	}

	if (localData)
		yaffs_ReleaseTempBuffer(dev, data, __LINE__);

	if (tags && retval == -EBADMSG && tags->eccResult == YAFFS_ECC_RESULT_NO_ERROR) {
		tags->eccResult = YAFFS_ECC_RESULT_UNFIXED;
		dev->eccUnfixed++;
	}
<<<<<<< HEAD
	if (tags && retval == -EUCLEAN && tags->eccResult == YAFFS_ECC_RESULT_NO_ERROR) {
=======
	if(tags && retval == -EUCLEAN && tags->eccResult == YAFFS_ECC_RESULT_NO_ERROR) {
>>>>>>> origin/incrediblec-2.6.32
		tags->eccResult = YAFFS_ECC_RESULT_FIXED;
		dev->eccFixed++;
	}
	if (retval == 0)
		return YAFFS_OK;
	else
		return YAFFS_FAIL;
}

int nandmtd2_MarkNANDBlockBad(struct yaffs_DeviceStruct *dev, int blockNo)
{
<<<<<<< HEAD
	struct mtd_info *mtd = (struct mtd_info *)(dev->genericDevice);
=======
	struct mtd_info *mtd = yaffs_DeviceToMtd(dev);
>>>>>>> origin/incrediblec-2.6.32
	int retval;
	T(YAFFS_TRACE_MTD,
	  (TSTR("nandmtd2_MarkNANDBlockBad %d" TENDSTR), blockNo));

	retval =
	    mtd->block_markbad(mtd,
<<<<<<< HEAD
			       blockNo * dev->nChunksPerBlock *
			       dev->totalBytesPerChunk);
=======
			       blockNo * dev->param.nChunksPerBlock *
			       dev->param.totalBytesPerChunk);
>>>>>>> origin/incrediblec-2.6.32

	if (retval == 0)
		return YAFFS_OK;
	else
		return YAFFS_FAIL;

}

int nandmtd2_QueryNANDBlock(struct yaffs_DeviceStruct *dev, int blockNo,
			    yaffs_BlockState *state, __u32 *sequenceNumber)
{
<<<<<<< HEAD
	struct mtd_info *mtd = (struct mtd_info *)(dev->genericDevice);
=======
	struct mtd_info *mtd = yaffs_DeviceToMtd(dev);
>>>>>>> origin/incrediblec-2.6.32
	int retval;

	T(YAFFS_TRACE_MTD,
	  (TSTR("nandmtd2_QueryNANDBlock %d" TENDSTR), blockNo));
	retval =
	    mtd->block_isbad(mtd,
<<<<<<< HEAD
			     blockNo * dev->nChunksPerBlock *
			     dev->totalBytesPerChunk);
=======
			     blockNo * dev->param.nChunksPerBlock *
			     dev->param.totalBytesPerChunk);
>>>>>>> origin/incrediblec-2.6.32

	if (retval) {
		T(YAFFS_TRACE_MTD, (TSTR("block is bad" TENDSTR)));

		*state = YAFFS_BLOCK_STATE_DEAD;
		*sequenceNumber = 0;
	} else {
		yaffs_ExtendedTags t;
		nandmtd2_ReadChunkWithTagsFromNAND(dev,
						   blockNo *
<<<<<<< HEAD
						   dev->nChunksPerBlock, NULL,
=======
						   dev->param.nChunksPerBlock, NULL,
>>>>>>> origin/incrediblec-2.6.32
						   &t);

		if (t.chunkUsed) {
			*sequenceNumber = t.sequenceNumber;
			*state = YAFFS_BLOCK_STATE_NEEDS_SCANNING;
		} else {
			*sequenceNumber = 0;
			*state = YAFFS_BLOCK_STATE_EMPTY;
		}
	}
	T(YAFFS_TRACE_MTD,
	  (TSTR("block is bad seq %d state %d" TENDSTR), *sequenceNumber,
	   *state));

	if (retval == 0)
		return YAFFS_OK;
	else
		return YAFFS_FAIL;
}

