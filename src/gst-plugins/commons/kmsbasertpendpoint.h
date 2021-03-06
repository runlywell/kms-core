/*
 * (C) Copyright 2013 Kurento (http://kurento.org/)
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
#ifndef __KMS_BASE_RTP_ENDPOINT_H__
#define __KMS_BASE_RTP_ENDPOINT_H__

#include "kmsbasesdpendpoint.h"
#include "kmsirtpconnection.h"
#include "kmsmediatype.h"
#include "kmsmediastate.h"

/* TODO: remove from here, it is defined in kmrtcp.h */
#define RTCP_MIN_INTERVAL 500 /* ms */

G_BEGIN_DECLS
/* #defines don't like whitespacey bits */
#define KMS_TYPE_BASE_RTP_ENDPOINT \
  (kms_base_rtp_endpoint_get_type())
#define KMS_BASE_RTP_ENDPOINT(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),KMS_TYPE_BASE_RTP_ENDPOINT,KmsBaseRtpEndpoint))
#define KMS_BASE_RTP_ENDPOINT_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),KMS_TYPE_BASE_RTP_ENDPOINT,KmsBaseRtpEndpointClass))
#define KMS_IS_BASE_RTP_ENDPOINT(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),KMS_TYPE_BASE_RTP_ENDPOINT))
#define KMS_IS_BASE_RTP_ENDPOINT_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),KMS_TYPE_BASE_RTP_ENDPOINT))
#define KMS_BASE_RTP_ENDPOINT_CAST(obj) ((KmsBaseRtpEndpoint*)(obj))

typedef struct _KmsBaseRtpEndpoint KmsBaseRtpEndpoint;
typedef struct _KmsBaseRtpEndpointClass KmsBaseRtpEndpointClass;
typedef struct _KmsBaseRtpEndpointPrivate KmsBaseRtpEndpointPrivate;

#define KMS_BASE_RTP_ENDPOINT_LOCK(elem) \
  (g_rec_mutex_lock (&KMS_BASE_RTP_ENDPOINT_CAST ((elem))->media_mutex))
#define KMS_BASE_RTP_ENDPOINT_UNLOCK(elem) \
  (g_rec_mutex_unlock (&KMS_BASE_RTP_ENDPOINT_CAST ((elem))->media_mutex))

/* rtpbin pad names */
#define RTPBIN_RECV_RTP_SINK "recv_rtp_sink_"
#define RTPBIN_RECV_RTCP_SINK "recv_rtcp_sink_"
#define RTPBIN_RECV_RTP_SRC "recv_rtp_src_"
#define RTPBIN_SEND_RTP_SRC "send_rtp_src_"
#define RTPBIN_SEND_RTCP_SRC "send_rtcp_src_"
#define RTPBIN_SEND_RTP_SINK "send_rtp_sink_"

#define AUDIO_STREAM_NAME "audio"
#define AUDIO_RTP_SESSION 0
#define AUDIO_RTP_SESSION_STR "0"
#define AUDIO_RTPBIN_RECV_RTP_SINK RTPBIN_RECV_RTP_SINK AUDIO_RTP_SESSION_STR
#define AUDIO_RTPBIN_RECV_RTCP_SINK RTPBIN_RECV_RTCP_SINK AUDIO_RTP_SESSION_STR
#define AUDIO_RTPBIN_RECV_RTP_SRC RTPBIN_RECV_RTP_SRC AUDIO_RTP_SESSION_STR
#define AUDIO_RTPBIN_SEND_RTP_SRC RTPBIN_SEND_RTP_SRC AUDIO_RTP_SESSION_STR
#define AUDIO_RTPBIN_SEND_RTCP_SRC RTPBIN_SEND_RTCP_SRC AUDIO_RTP_SESSION_STR
#define AUDIO_RTPBIN_SEND_RTP_SINK RTPBIN_SEND_RTP_SINK AUDIO_RTP_SESSION_STR

#define VIDEO_STREAM_NAME "video"
#define VIDEO_RTP_SESSION 1
#define VIDEO_RTP_SESSION_STR "1"
#define VIDEO_RTPBIN_RECV_RTP_SINK RTPBIN_RECV_RTP_SINK VIDEO_RTP_SESSION_STR
#define VIDEO_RTPBIN_RECV_RTCP_SINK RTPBIN_RECV_RTCP_SINK VIDEO_RTP_SESSION_STR
#define VIDEO_RTPBIN_RECV_RTP_SRC RTPBIN_RECV_RTP_SRC VIDEO_RTP_SESSION_STR
#define VIDEO_RTPBIN_SEND_RTP_SRC RTPBIN_SEND_RTP_SRC VIDEO_RTP_SESSION_STR
#define VIDEO_RTPBIN_SEND_RTCP_SRC RTPBIN_SEND_RTCP_SRC VIDEO_RTP_SESSION_STR
#define VIDEO_RTPBIN_SEND_RTP_SINK RTPBIN_SEND_RTP_SINK VIDEO_RTP_SESSION_STR

#define BUNDLE_STREAM_NAME "bundle"

/* RTP/RTCP profiles */
#define SDP_MEDIA_RTP_AVP_PROTO "RTP/AVP"
#define SDP_MEDIA_RTP_SAVPF_PROTO "RTP/SAVPF"

#define RTCP_MUX "rtcp-mux"

/* RTP enconding names */
#define OPUS_ENCONDING_NAME "OPUS"
#define VP8_ENCONDING_NAME "VP8"

struct _KmsBaseRtpEndpoint
{
  KmsBaseSdpEndpoint parent;

  KmsBaseRtpEndpointPrivate *priv;
};

struct _KmsBaseRtpEndpointClass
{
  KmsBaseSdpEndpointClass parent_class;

  void (*media_start) (KmsBaseRtpEndpoint * self, KmsMediaType type,
    gboolean local);
  void (*media_stop) (KmsBaseRtpEndpoint * self, KmsMediaType type,
    gboolean local);
  void (*media_state_changed) (KmsBaseRtpEndpoint * self, KmsMediaState new_state);

  gboolean (*request_local_key_frame) (KmsBaseRtpEndpoint * self);

  /* virtual methods */
  KmsIRtpConnection * (*create_connection) (KmsBaseRtpEndpoint * self, SdpMediaConfig * mconf, const gchar *name);
  KmsIRtcpMuxConnection* (*create_rtcp_mux_connection) (KmsBaseRtpEndpoint * self, const gchar *name);
  KmsIBundleConnection * (*create_bundle_connection) (KmsBaseRtpEndpoint * self, const gchar *name);
};

GType kms_base_rtp_endpoint_get_type (void);

KmsIRtpConnection * kms_base_rtp_endpoint_get_connection (KmsBaseRtpEndpoint * selff, SdpMediaConfig *mconf);
GHashTable * kms_base_rtp_endpoint_get_connections (KmsBaseRtpEndpoint * self);

G_END_DECLS
#endif /* __KMS_BASE_RTP_ENDPOINT_H__ */
