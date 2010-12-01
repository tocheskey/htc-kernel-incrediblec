/*
 * YAFFS: Yet another Flash File System . A NAND-flash specific file system.
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
 * it under the terms of the GNU Lesser General Public License version 2.1 as
 * published by the Free Software Foundation.
 *
 * Note: Only YAFFS headers are LGPL, YAFFS C code is covered by GPL.
 */


#ifndef __YPORTENV_H__
#define __YPORTENV_H__

/*
 * Define the MTD version in terms of Linux Kernel versions
 * This allows yaffs to be used independantly of the kernel
 * as well as with it.
 */

#define MTD_VERSION(a, b, c) (((a) << 16) + ((b) << 8) + (c))

#if defined CONFIG_YAFFS_WINCE

#include "ywinceenv.h"

#elif defined __KERNEL__

#include "moduleconfig.h"

/* Linux kernel */

#include <linux/version.h>
#define MTD_VERSION_CODE LINUX_VERSION_CODE

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 19))
#include <linux/config.h>
#endif
<<<<<<< HEAD
=======

>>>>>>> origin/incrediblec-2.6.32
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
<<<<<<< HEAD
=======
#include <linux/xattr.h>
>>>>>>> origin/incrediblec-2.6.32

#define YCHAR char
#define YUCHAR unsigned char
#define _Y(x)     x
#define yaffs_strcat(a, b)     strcat(a, b)
#define yaffs_strcpy(a, b)     strcpy(a, b)
#define yaffs_strncpy(a, b, c) strncpy(a, b, c)
#define yaffs_strncmp(a, b, c) strncmp(a, b, c)
<<<<<<< HEAD
#define yaffs_strlen(s)	       strlen(s)
#define yaffs_sprintf	       sprintf
#define yaffs_toupper(a)       toupper(a)

#define Y_INLINE inline
=======
#define yaffs_strnlen(s,m)	strnlen(s,m)
#define yaffs_sprintf	       sprintf
#define yaffs_toupper(a)       toupper(a)

#define Y_INLINE __inline__
>>>>>>> origin/incrediblec-2.6.32

#define YAFFS_LOSTNFOUND_NAME		"lost+found"
#define YAFFS_LOSTNFOUND_PREFIX		"obj"

/* #define YPRINTF(x) printk x */
#define YMALLOC(x) kmalloc(x, GFP_NOFS)
#define YFREE(x)   kfree(x)
#define YMALLOC_ALT(x) vmalloc(x)
#define YFREE_ALT(x)   vfree(x)
#define YMALLOC_DMA(x) YMALLOC(x)

<<<<<<< HEAD
/* KR - added for use in scan so processes aren't blocked indefinitely. */
#define YYIELD() schedule()

#define YAFFS_ROOT_MODE			0666
#define YAFFS_LOSTNFOUND_MODE		0666
=======
#define YYIELD() schedule()
#define Y_DUMP_STACK() dump_stack()

#define YAFFS_ROOT_MODE			0755
#define YAFFS_LOSTNFOUND_MODE		0700
>>>>>>> origin/incrediblec-2.6.32

#if (LINUX_VERSION_CODE > KERNEL_VERSION(2, 5, 0))
#define Y_CURRENT_TIME CURRENT_TIME.tv_sec
#define Y_TIME_CONVERT(x) (x).tv_sec
#else
#define Y_CURRENT_TIME CURRENT_TIME
#define Y_TIME_CONVERT(x) (x)
#endif

#define yaffs_SumCompare(x, y) ((x) == (y))
#define yaffs_strcmp(a, b) strcmp(a, b)

#define TENDSTR "\n"
<<<<<<< HEAD
#define TSTR(x) KERN_WARNING x
#define TCONT(x) x
#define TOUT(p) printk p

#define yaffs_trace(mask, fmt, args...) \
	do { if ((mask) & (yaffs_traceMask|YAFFS_TRACE_ERROR)) \
		printk(KERN_WARNING "yaffs: " fmt, ## args); \
	} while (0)

=======
#define TSTR(x) KERN_DEBUG x
#define TCONT(x) x
#define TOUT(p) printk p

>>>>>>> origin/incrediblec-2.6.32
#define compile_time_assertion(assertion) \
	({ int x = __builtin_choose_expr(assertion, 0, (void)0); (void) x; })

#elif defined CONFIG_YAFFS_DIRECT

#define MTD_VERSION_CODE MTD_VERSION(2, 6, 22)

/* Direct interface */
#include "ydirectenv.h"

#elif defined CONFIG_YAFFS_UTIL

/* Stuff for YAFFS utilities */

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

<<<<<<< HEAD
#include "devextras.h"
=======
>>>>>>> origin/incrediblec-2.6.32

#define YMALLOC(x) malloc(x)
#define YFREE(x)   free(x)
#define YMALLOC_ALT(x) malloc(x)
#define YFREE_ALT(x) free(x)

#define YCHAR char
#define YUCHAR unsigned char
#define _Y(x)     x
#define yaffs_strcat(a, b)     strcat(a, b)
#define yaffs_strcpy(a, b)     strcpy(a, b)
#define yaffs_strncpy(a, b, c) strncpy(a, b, c)
<<<<<<< HEAD
#define yaffs_strlen(s)	       strlen(s)
=======
#define yaffs_strnlen(s,m)	       strnlen(s,m)
>>>>>>> origin/incrediblec-2.6.32
#define yaffs_sprintf	       sprintf
#define yaffs_toupper(a)       toupper(a)

#define Y_INLINE inline

/* #define YINFO(s) YPRINTF(( __FILE__ " %d %s\n",__LINE__,s)) */
/* #define YALERT(s) YINFO(s) */

#define TENDSTR "\n"
#define TSTR(x) x
#define TOUT(p) printf p

#define YAFFS_LOSTNFOUND_NAME		"lost+found"
#define YAFFS_LOSTNFOUND_PREFIX		"obj"
/* #define YPRINTF(x) printf x */

<<<<<<< HEAD
#define YAFFS_ROOT_MODE				0666
#define YAFFS_LOSTNFOUND_MODE		0666
=======
#define YAFFS_ROOT_MODE			0755
#define YAFFS_LOSTNFOUND_MODE		0700
>>>>>>> origin/incrediblec-2.6.32

#define yaffs_SumCompare(x, y) ((x) == (y))
#define yaffs_strcmp(a, b) strcmp(a, b)

#else
/* Should have specified a configuration type */
#error Unknown configuration

#endif

<<<<<<< HEAD
/* see yaffs_fs.c */
extern unsigned int yaffs_traceMask;
extern unsigned int yaffs_wr_attempts;

/*
 * Tracing flags.
 * The flags masked in YAFFS_TRACE_ALWAYS are always traced.
 */

#define YAFFS_TRACE_OS			0x00000002
#define YAFFS_TRACE_ALLOCATE		0x00000004
#define YAFFS_TRACE_SCAN		0x00000008
#define YAFFS_TRACE_BAD_BLOCKS		0x00000010
#define YAFFS_TRACE_ERASE		0x00000020
#define YAFFS_TRACE_GC			0x00000040
#define YAFFS_TRACE_WRITE		0x00000080
#define YAFFS_TRACE_TRACING		0x00000100
#define YAFFS_TRACE_DELETION		0x00000200
#define YAFFS_TRACE_BUFFERS		0x00000400
#define YAFFS_TRACE_NANDACCESS		0x00000800
#define YAFFS_TRACE_GC_DETAIL		0x00001000
#define YAFFS_TRACE_SCAN_DEBUG		0x00002000
#define YAFFS_TRACE_MTD			0x00004000
#define YAFFS_TRACE_CHECKPOINT		0x00008000

#define YAFFS_TRACE_VERIFY		0x00010000
#define YAFFS_TRACE_VERIFY_NAND		0x00020000
#define YAFFS_TRACE_VERIFY_FULL		0x00040000
#define YAFFS_TRACE_VERIFY_ALL		0x000F0000
#define YAFFS_TRACE_HTC_DEBUG		0x00100000

#define YAFFS_TRACE_ERROR		0x40000000
#define YAFFS_TRACE_BUG			0x80000000
#define YAFFS_TRACE_ALWAYS		0xF0000000


#define T(mask, p) do { if ((mask) & (yaffs_traceMask | YAFFS_TRACE_ALWAYS)) TOUT(p); } while (0)

#ifndef YBUG
#define YBUG() do {T(YAFFS_TRACE_BUG, (TSTR("==>> yaffs bug: " __FILE__ " %d" TENDSTR), __LINE__)); } while (0)
#endif

=======
#if defined(CONFIG_YAFFS_DIRECT) || defined(CONFIG_YAFFS_WINCE)

#ifdef CONFIG_YAFFSFS_PROVIDE_VALUES

#ifndef O_RDONLY
#define O_RDONLY        00
#endif

#ifndef O_WRONLY
#define O_WRONLY	01
#endif

#ifndef O_RDWR
#define O_RDWR		02
#endif

#ifndef O_CREAT		
#define O_CREAT 	0100
#endif

#ifndef O_EXCL
#define O_EXCL		0200
#endif

#ifndef O_TRUNC
#define O_TRUNC		01000
#endif

#ifndef O_APPEND
#define O_APPEND	02000
#endif

#ifndef SEEK_SET
#define SEEK_SET	0
#endif

#ifndef SEEK_CUR
#define SEEK_CUR	1
#endif

#ifndef SEEK_END
#define SEEK_END	2
#endif

#ifndef EBUSY
#define EBUSY	16
#endif

#ifndef ENODEV
#define ENODEV	19
#endif

#ifndef EINVAL
#define EINVAL	22
#endif

#ifndef EBADF
#define EBADF	9
#endif

#ifndef EACCES
#define EACCES	13
#endif

#ifndef EXDEV	
#define EXDEV	18
#endif

#ifndef ENOENT
#define ENOENT	2
#endif

#ifndef ENOSPC
#define ENOSPC	28
#endif

#ifndef ERANGE
#define ERANGE 34
#endif

#ifndef ENODATA
#define ENODATA 61
#endif

#ifndef ENOTEMPTY
#define ENOTEMPTY 39
#endif

#ifndef ENAMETOOLONG
#define ENAMETOOLONG 36
#endif

#ifndef ENOMEM
#define ENOMEM 12
#endif

#ifndef EEXIST
#define EEXIST 17
#endif

#ifndef ENOTDIR
#define ENOTDIR 20
#endif

#ifndef EISDIR
#define EISDIR 21
#endif


// Mode flags

#ifndef S_IFMT
#define S_IFMT		0170000
#endif

#ifndef S_IFLNK
#define S_IFLNK		0120000
#endif

#ifndef S_IFDIR
#define S_IFDIR		0040000
#endif

#ifndef S_IFREG
#define S_IFREG		0100000
#endif

#ifndef S_IREAD 
#define S_IREAD		0000400
#endif

#ifndef S_IWRITE
#define	S_IWRITE	0000200
#endif

#ifndef S_IEXEC
#define	S_IEXEC	0000100
#endif

#ifndef XATTR_CREATE
#define XATTR_CREATE 1
#endif

#ifndef XATTR_REPLACE
#define XATTR_REPLACE 2
#endif

#ifndef R_OK
#define R_OK	4
#define W_OK	2
#define X_OK	1
#define F_OK	0
#endif

#else
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif

#endif

#ifndef Y_DUMP_STACK
#define Y_DUMP_STACK() do { } while (0)
#endif

#ifndef YBUG
#define YBUG() do {\
	T(YAFFS_TRACE_BUG,\
		(TSTR("==>> yaffs bug: " __FILE__ " %d" TENDSTR),\
		__LINE__));\
	Y_DUMP_STACK();\
} while (0)
#endif


>>>>>>> origin/incrediblec-2.6.32
#endif
