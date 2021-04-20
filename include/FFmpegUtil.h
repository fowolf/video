//
// Created by zhichao.tian on 2021/4/9.
//

#ifndef VIDEO_FFMPEGUTIL_H
#define VIDEO_FFMPEGUTIL_H

//引入ffmpeg头文件
extern "C" {
#include "libavutil/opt.h"
#include "libavutil/time.h"
#include "libavutil/frame.h"
#include "libavutil/pixdesc.h"
#include "libavutil/avassert.h"
#include "libavutil/imgutils.h"
#include "libavutil/ffversion.h"
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"
#include "libavformat/avformat.h"
#include "libavfilter/avfilter.h"
#ifndef gcc45
#include "libavutil/hwcontext.h"
#endif
}


class FFmpegUtil {
private:
    int videoIndex;
public:
    explicit FFmpegUtil();

    int initDecodeVideo();
    void openUsb(int);

};


#endif //VIDEO_FFMPEGUTIL_H
