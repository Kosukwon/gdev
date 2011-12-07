/*
 * Copyright 2011 Shinpei Kato
 *
 * University of California at Santa Cruz
 * Systems Research Lab.
 *
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __GDEV_PROTO_H__
#define __GDEV_PROTO_H__

#include "gdev_conf.h"

/**
 * Gdev types: they are not exposed to end users.
 */
typedef struct gdev_vas gdev_vas_t;
typedef struct gdev_ctx gdev_ctx_t;
typedef struct gdev_mem gdev_mem_t;
typedef struct gdev_device gdev_device_t;

/**
 * Gdev device struct:
 */
struct gdev_device {
	int id;
	int use; /* the number of threads/processes using the device. */
	uint32_t chipset;
	void *priv; /* private device object */
	void *compute; /* private set of compute functions */
};

/**
 * runtime/driver-dependent resource management functions.
 */
int gdev_compute_init(gdev_device_t *);
int gdev_query(gdev_device_t *, uint32_t, uint32_t *);
gdev_device_t *gdev_dev_open(int);
void gdev_dev_close(gdev_device_t *);
gdev_vas_t *gdev_vas_new(gdev_device_t *, uint64_t);
void gdev_vas_free(gdev_vas_t *);
gdev_ctx_t *gdev_ctx_new(gdev_device_t *, gdev_vas_t *);
void gdev_ctx_free(gdev_ctx_t *);
gdev_mem_t *gdev_malloc(gdev_vas_t *, uint64_t, int);
void gdev_free(gdev_mem_t *);

/**
 * runtime/driver/architecture-independent compute functions.
 */
uint32_t gdev_memcpy(gdev_ctx_t *, uint64_t, uint64_t, uint32_t);
uint32_t gdev_launch(gdev_ctx_t *, struct gdev_kernel *);
int gdev_poll(gdev_ctx_t *, int, uint32_t, struct gdev_time *);

/**
 * runtime/driver/architecture-independent heap operations.
 */
void gdev_heap_init(gdev_vas_t *);
void gdev_heap_add(gdev_mem_t *, int);
void gdev_heap_del(gdev_mem_t *);
gdev_mem_t *gdev_heap_lookup(gdev_vas_t *, uint64_t, int);
void gdev_garbage_collect(gdev_vas_t *);

#endif