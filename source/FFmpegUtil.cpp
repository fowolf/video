//
// Created by zhichao.tian on 2021/4/9.
//

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "../include/CFps.h"
#include "../include/FFmpegUtil.h"
#include "../include/CFileUtils.h"
#include "../include/CLogUtils.h"

using namespace std;

log4cpp::Category &FFmpegUtil::logger = CLogUtils::getDefaultLogger("FFmpegUtils");

void FFmpegUtil::openTs(std::string tsPath)
{
    if (!CFileUtils::isFileExists(tsPath.c_str()))
    {
        logger.info("file: %s not exists.", tsPath.c_str());
        return;
    }

    av_register_all();
    AVFormatContext *pFormatCtx = NULL;
    AVCodec *pCodec = NULL;
    AVCodecContext *pCodecCtxOrig = NULL;
    AVCodecContext *pCodecCtx = NULL;

    if (avformat_open_input(&pFormatCtx, tsPath.c_str(), NULL, NULL) != 0)
    {
        return;
    }
    av_dump_format(pFormatCtx, 0, tsPath.c_str(), 0);
    assert(avformat_find_stream_info(pFormatCtx, NULL) >= 0);

    int i, video_stream = -1;
    for (i = 0; i < pFormatCtx->nb_streams; i++)
    {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            video_stream = i;
            break;
        }
    }
    if (-1 == video_stream)
    {
        logger.info("no video stream detected");
        return;
    }

    pCodecCtx = pFormatCtx->streams[video_stream]->codec;

    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    if (NULL == pCodec)
    {
        logger.info("unsupported codec.\n");
        return;
    }

    pCodecCtxOrig = avcodec_alloc_context3(pCodec);
    if (avcodec_copy_context(pCodecCtxOrig, pCodecCtx) != 0)
    {
        logger.info("couldn't copy codec context\n");
        return;
    }

    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
    {
        printf("couldn't open codec\n");
        return;
    }

    AVFrame *pFrame = av_frame_alloc();
    AVFrame *pFrameBgr = av_frame_alloc();
    assert(pFrame && pFrameBgr);

    int numBytes = avpicture_get_size(AV_PIX_FMT_BGR24,
                                      pCodecCtx->width,
                                      pCodecCtx->height);

    auto *buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));

    avpicture_fill((AVPicture *)pFrameBgr,
                   buffer,
                   AV_PIX_FMT_BGR24,
                   pCodecCtx->width,
                   pCodecCtx->height);

    
    
    struct SwsContext *sws_ctx = sws_getContext(pCodecCtx->width,
                                                pCodecCtx->height,
                                                pCodecCtx->pix_fmt,
                                                pCodecCtx->width,
                                                pCodecCtx->height,
                                                AV_PIX_FMT_BGR24,
                                                SWS_BILINEAR,
                                                NULL,
                                                NULL,
                                                NULL);
    int w = pCodecCtx->width;
    int h = pCodecCtx->height;
    int frame_finished;
    cv::Mat mBGR(cv::Size(w, h), CV_8UC3);
    AVPacket* packet;
    packet = av_packet_alloc();
    if (!packet)
        exit(1);

    i = 0;
    while (av_read_frame(pFormatCtx, packet) >= 0)
    {
        if ((*packet).stream_index != video_stream)
        {
            continue;
        }
        /*
        int avcodec_decode_video2(AVCodecContext *avctx, AVFrame *picture,
                         int *got_picture_ptr,
                         const AVPacket *avpkt);

        int avcodec_receive_frame(AVCodecContext *avctx, AVFrame *frame);
        int avcodec_send_packet(AVCodecContext *avctx, const AVPacket *avpkt);
        */
        // avcodec_decode_video2(pCodecCtx, pFrame, &frame_finished, packet);

        int ret = avcodec_send_packet(pCodecCtx, packet);
        frame_finished = avcodec_receive_frame(pCodecCtx, pFrame); 

        if (!frame_finished)
            continue;

        sws_scale(sws_ctx,
                  pFrame->data,
                  pFrame->linesize,
                  0,
                  pCodecCtx->height,
                  pFrameBgr->data,
                  pFrameBgr->linesize);

        mBGR.data = (uchar *)pFrameBgr->data[0];
        // cv::imshow("Display Image", mBGR);
        // int key = cv::waitKey(200);
        // if ((char)key == 'q')
        // {
        //     break;
        // }
        cv::imwrite("/dev/shm/video/bbb.bmp", mBGR);
        i++;
        printf("i");
    }
    av_packet_unref(packet);

    // free the RGB image
    av_free(buffer);
    av_free(pFrameBgr);
    // free raw frame
    av_free(pFrame);
    // close codecs
    avcodec_close(pCodecCtx);
    avcodec_close(pCodecCtxOrig);
    // close video file
    avformat_close_input(&pFormatCtx);

    printf("finished\n");
    return;
}
