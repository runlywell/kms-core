/*
 * (C) Copyright 2014 Kurento (http://kurento.org/)
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU Lesser General Public License
 * (LGPL) version 2.1 which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/lgpl-2.1.html
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 */

#ifndef __KMS_REMB_H__
#define __KMS_REMB_H__

#include "kmsutils.h" /* TODO: must be not needed */

G_BEGIN_DECLS

#define KMS_REMB_BASE(obj) ((KmsRembBase *)(obj))

#define KMS_REMB_BASE_LOCK(obj) \
  (g_rec_mutex_lock (&KMS_REMB_BASE(obj)->mutex))
#define KMS_REMB_BASE_UNLOCK(obj) \
  (g_rec_mutex_unlock (&KMS_REMB_BASE(obj)->mutex))

typedef struct _KmsRembBase KmsRembBase;

struct _KmsRembBase
{
  GObject *rtpsess;
  GRecMutex mutex;
  GHashTable *remb_stats;
  guint session;
  gulong signal_id;
};

/* KmsRembLocal begin */
typedef struct _KmsRembLocal KmsRembLocal;

struct _KmsRembLocal
{
  KmsRembBase base;

  guint remote_ssrc;
  guint min_bw;
  guint max_bw;

  guint remb;
  gboolean probed;
  guint threshold;
  guint lineal_factor;
  guint max_br;
  guint avg_br;
  GstClockTime last_time;
  guint64 last_octets_received;
  RembEventManager *event_manager;
};

KmsRembLocal * kms_remb_local_create (GObject *rtpsess, guint session,
  guint remote_ssrc, guint min_bw, guint max_bw);
void kms_remb_local_destroy (KmsRembLocal *rl);
/* KmsRembLocal end */

/* KmsRembRemote begin */
typedef struct _KmsRembRemote KmsRembRemote;

struct _KmsRembRemote
{
  KmsRembBase base;

  guint local_ssrc;
  guint min_bw;
  guint max_bw;

  guint remb;
  gboolean probed;
  GstPad *pad_event;
};

KmsRembRemote * kms_remb_remote_create (GObject *rtpsess, guint session,
  guint local_ssrc, guint min_bw, guint max_bw, GstPad * pad);
void kms_remb_remote_destroy (KmsRembRemote *rm);
/* KmsRembRemote end */

G_END_DECLS
#endif /* __KMS_REMB_H__ */
