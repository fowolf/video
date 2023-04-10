//
// Created by zhichao.tian on 2021/4/9.
//

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
// #include <libavutil/imgutils.h>

#include "../include/CFps.h"
#include "../include/FFmpegUtil.h"
#include "../include/CFileUtils.h"
#include "../include/CLogUtils.h"

using namespace std;

log4cpp::Category &FFmpegUtil::logger = CLogUtils::getDefaultLogger("FFmpegUtils");

void FFmpegUtil::openTs(std::string tsPath)
{
    if (!CFileUtils::IsFileExists(tsPath.c_str()))
    {
        logger.info("file: %s not exists.", tsPath.c_str());
        return;
    }

    // av_register_all();
    AVFormatContext *pFormatCtx = NULL;
    AVCodec *pCodec = NULL;
    // AVCodecContext *pCodecCtxOrig = NULL;
    AVCodecContext *pCodecCtx = NULL;
    AVCodecParameters *pCodecParams = NULL;

    if (avformat_open_input(&pFormatCtx, tsPath.c_str(), NULL, NULL) != 0)
    {
        return;
    }
    av_dump_format(pFormatCtx, 0, tsPath.c_str(), 0);
    assert(avformat_find_stream_info(pFormatCtx, NULL) >= 0);

    int i, video_stream = -1;
    for (i = 0; i < pFormatCtx->nb_streams; i++)
    {
        // if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
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

    pCodecParams = pFormatCtx->streams[video_stream]->codecpar;

    pCodec = avcodec_find_decoder(pCodecParams->codec_id);
    if (NULL == pCodec)
    {
        logger.info("unsupported codec.\n");
        return;
    }

    pCodecCtx = avcodec_alloc_context3(pCodec);
    avcodec_parameters_to_context(pCodecCtx, pCodecParams);
    // pCodecCtxOrig = avcodec_alloc_context3(pCodec);
    // if (avcodec_copy_context(pCodecCtxOrig, pCodecCtx) != 0)
    // {
    //     logger.info("couldn't copy codec context\n");
    //     return;
    // }

    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
    {
        logger.info("couldn't open codec\n");
        return;
    }

    AVFrame *pFrame = av_frame_alloc();
    AVFrame *pFrameBgr = av_frame_alloc();
    assert(pFrame && pFrameBgr);

    // int numBytes = avpicture_get_size(AV_PIX_FMT_BGR24,
    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_BGR24,
                                            pCodecParams->width,
                                            pCodecParams->height, 1);

    auto *buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));

    // avpicture_fill((AVPicture *)pFrameBgr,
    //                buffer,
    //                AV_PIX_FMT_BGR24,
    //                pCodecParams->width,
    //                pCodecParams->height);

    av_image_fill_arrays(pFrameBgr->data, pFrameBgr->linesize,
                         buffer,
                         AV_PIX_FMT_BGR24,
                         pCodecParams->width,
                         pCodecParams->height, 1);

    struct SwsContext *sws_ctx = sws_getContext(pCodecParams->width,
                                                pCodecParams->height,
                                                pCodecCtx->pix_fmt,
                                                pCodecParams->width,
                                                pCodecParams->height,
                                                AV_PIX_FMT_BGR24,
                                                SWS_BILINEAR,
                                                NULL,
                                                NULL,
                                                NULL);
    int w = pCodecParams->width;
    int h = pCodecParams->height;
    int frame_finished;
    cv::Mat mBGR(cv::Size(w, h), CV_8UC3);
    AVPacket *packet;
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

        if (frame_finished != 0)
            continue;

        sws_scale(sws_ctx,
                  pFrame->data,
                  pFrame->linesize,
                  0,
                  pCodecParams->height,
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
        logger.info("save frame: %d", i);
        i++;
    }
    av_packet_unref(packet);

    // free the RGB image
    av_free(buffer);
    av_free(pFrameBgr);
    // free raw frame
    av_free(pFrame);
    // close codecs
    avcodec_close(pCodecCtx);
    // avcodec_close(pCodecCtxOrig);

    // close video file
    avformat_close_input(&pFormatCtx);

    // avcodec_parameters_free(&pCodecParams);
    logger.info("finished\n");
    return;
}
