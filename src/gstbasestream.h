#ifndef __GST_BASE_STREAM_H__
#define __GST_BASE_STREAM_H__

#include <gst/gst.h>
#include <gst/sdp/gstsdpmessage.h>
#include <gstjoinable.h>

G_BEGIN_DECLS
/* #defines don't like whitespacey bits */
#define GST_TYPE_BASE_STREAM \
  (gst_base_stream_get_type())
#define GST_BASE_STREAM(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_BASE_STREAM,GstBaseStream))
#define GST_BASE_STREAM_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_BASE_STREAM,GstBaseStreamClass))
#define GST_IS_BASE_STREAM(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_BASE_STREAM))
#define GST_IS_BASE_STREAM_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_BASE_STREAM))
#define GST_BASE_STREAM_CAST(obj) ((GstBaseStream*)(obj))
typedef struct _GstBaseStream GstBaseStream;
typedef struct _GstBaseStreamClass GstBaseStreamClass;

#define GST_BASE_STREAM_LOCK(elem) \
  (g_rec_mutex_lock (&GST_BASE_STREAM_CAST ((elem))->media_mutex))
#define GST_BASE_STREAM_UNLOCK(elem) \
  (g_rec_mutex_unlock (&GST_BASE_STREAM_CAST ((elem))->media_mutex))

struct _GstBaseStream
{
  GstJoinable parent;
};

struct _GstBaseStreamClass
{
  GstJoinableClass parent_class;

  /* actions */
  GstSDPMessage *(*generate_offer) (GstBaseStream * base_stream);
  GstSDPMessage *(*generate_answer) (GstBaseStream * base_stream,
      GstSDPMessage * offer);
  void (*process_answer) (GstBaseStream * base_stream, GstSDPMessage * answer);
};

GType gst_base_stream_get_type (void);

G_END_DECLS
#endif /* __GST_BASE_STREAM_H__ */