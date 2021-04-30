//
// Created by zhichao.tian on 2021/4/9.
//

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <CFps.h>
#include "../include/FFmpegUtil.h"


FFmpegUtil::FFmpegUtil() {
    this->videoIndex = -1;
}

void FFmpegUtil::openUsb(int usbVideoIndex) {
    this->videoIndex = usbVideoIndex;


}


void FFmpegUtil::openRtsp(const std::string &rtsp) {
    AVFormatContext *pFormatCtx;
    AVCodecContext *pCodecCtx;
    AVCodec *pCodec;
    AVFrame *pFrame, *pFrameRGB;
    AVPacket *packet;
    uint8_t *out_buffer;

    static struct SwsContext *img_convert_ctx;

    int videoStream, i, numBytes;
    int ret, got_picture;

    avformat_network_init();   ///初始化FFmpeg网络模块，2017.8.5---lizhen
//    av_register_all();         //初始化FFMPEG  调用了这个才能正常适用编码器和解码器
    //Allocate an AVFormatContext.
    pFormatCtx = avformat_alloc_context();

    AVDictionary *avdic = nullptr;
    char option_key[] = "rtsp_transport";
    char option_value[] = "tcp";
    av_dict_set(&avdic, option_key, option_value, 0);
    char option_key2[] = "max_delay";
    char option_value2[] = "100";
    av_dict_set(&avdic, option_key2, option_value2, 0);
    char option_key3[] = "buffer_size";
    char option_value3[] = "0";
//    av_dict_set(&avdic, option_key3, option_value3, 0);

    if (avformat_open_input(&pFormatCtx, rtsp.c_str(), nullptr, &avdic) != 0) {
        printf("can't open the file. \n");
        return;
    }

    if (avformat_find_stream_info(pFormatCtx, nullptr) < 0) {
        printf("Could't find stream info.\n");
        return;
    }

    videoStream = -1;

    ///循环查找视频中包含的流信息，直到找到视频类型的流
    ///便将其记录下来 保存到videoStream变量中
    ///这里我们现在只处理视频流  音频流先不管他
    for (i = 0; i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStream = i;
        }
    }

    ///如果videoStream为-1 说明没有找到视频流
    if (videoStream == -1) {
        printf("Didn't find a video stream.\n");
        return;
    }

    ///查找解码器
    pCodecCtx = pFormatCtx->streams[videoStream]->codec;
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);

    pCodecCtx->bit_rate = 0;   //初始化为0
    pCodecCtx->time_base.num = 1;  //下面两行：一秒钟25帧
    pCodecCtx->time_base.den = 10;
    pCodecCtx->frame_number = 1;  //每包一个视频帧

    if (nullptr == pCodec) {
        printf("Codec not found.\n");
        return;
    }

    ///打开解码器
    if (avcodec_open2(pCodecCtx, pCodec, nullptr) < 0) {
        printf("Could not open codec.\n");
        return;
    }

    pFrame = av_frame_alloc();
    pFrameRGB = av_frame_alloc();

    ///这里我们改成了 将解码后的YUV数据转换成RGB32
    img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height,
                                     pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height,
                                     AV_PIX_FMT_RGB32, SWS_BICUBIC, NULL, NULL, NULL);

    numBytes = avpicture_get_size(AV_PIX_FMT_RGB32, pCodecCtx->width, pCodecCtx->height);

    out_buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));
    avpicture_fill((AVPicture *) pFrameRGB, out_buffer, AV_PIX_FMT_RGB32,
                   pCodecCtx->width, pCodecCtx->height);

    int y_size = pCodecCtx->width * pCodecCtx->height;

    packet = (AVPacket *) malloc(sizeof(AVPacket)); //分配一个packet
    av_new_packet(packet, y_size); //分配packet的数据

    cv::Mat img = cv::Mat::zeros(pCodecCtx->height, pCodecCtx->width, CV_8UC4);
    cv::Mat imgResize = cv::Mat::zeros(pCodecCtx->height/2, pCodecCtx->width/2, CV_8UC4);
    while (true) {
        if (av_read_frame(pFormatCtx, packet) < 0) {
            break; //这里认为视频读取完了
        }

        if (packet->stream_index == videoStream) {
            ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);

            if (ret < 0) {
                printf("decode error.\n");
                return;
            }
            if (got_picture) {
                sws_scale(img_convert_ctx,
                          (uint8_t const *const *) pFrame->data,
                          pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data,
                          pFrameRGB->linesize);
                //把这个RGB数据 用QImage加载
                memcpy(img.data, out_buffer, numBytes);

                cv::resize(img, imgResize, imgResize.size(), 0, 0);
                cv::namedWindow("ffmpeg", cv::WINDOW_AUTOSIZE);
                cv::imshow("ffmpeg", imgResize);
                cv::imwrite("/dev/shm/ddd.bmp", img);
                int key = cv::waitKey(1);
                if ((char) key == 'q') {
                    break;
                }
            } else {
                std::cout << "i'm sleep ...." << std::endl;
                av_usleep(10000);
                std::cout << "i'm sleep ed ...." << std::endl;
            }
        }
        av_free_packet(packet); //释放资源,否则内存会一直上升
        std::cout << "fps:" << CFps::statFps() << std::endl;
    }
    av_free(out_buffer);
    av_free(pFrameRGB);
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);
}
