/* SPDX-FileCopyrightText: 2013 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

/** \file
 * \ingroup openimageio
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Initialize OpenImageIO on startup.
 */
void OIIO_init(void);

/*
 * Get OpenImageIO version.
 */
int OIIO_getVersionHex(void);

#ifdef __cplusplus
}

#endif