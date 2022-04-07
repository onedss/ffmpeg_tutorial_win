//
// Created by yzymi on 2022-04-05.
//

#include <iostream>
#include <fstream>
#include <sdl/SDL.h>
#undef main
using namespace std;

void AudioCallback(void* userdata, Uint8* stream, int len)
{
    cout << "AudioCallback" << endl;
    SDL_memset(stream, 0, len);
    auto ifs = (ifstream*)userdata;
    ifs->read((char*)stream, len);
    if (ifs->gcount() <= 0)
    {
        SDL_PauseAudio(1);
    }
}

int main(int argc, char **argv) {
    //初始化 SDL 音频模块
    SDL_Init(SDL_INIT_AUDIO);

    //打开音频设备
    SDL_AudioSpec spec;
    spec.freq = 44100;          //音频一秒采样率
    spec.format = AUDIO_S16SYS; //音频样本类型 使用系统字节序
    spec.channels = 2;          //音频通道数量（双声道 立体声）
    spec.silence = 0;           //静音的值
    spec.samples = 1024;        //样本数量，2的n次方，用于分割
    //平面模式的多通道数据
    //例如： samples = 8
    //      LLLL RRRR
    spec.callback = AudioCallback;//音频播放回调函数
    ifstream ifs("test_pcm.pcm",ios::binary);//二进制打开
    if (!ifs)
    {
        cerr << "open pcm file failed!" << endl;
        return -1;
    }
    spec.userdata = &ifs;

    if (SDL_OpenAudio(&spec, nullptr) < 0)
    {
        cerr << "SDL_OpenAudio failed" << SDL_GetError() << endl;
        return -1;
    }
    SDL_PauseAudio(0);
    getchar();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);


    return 0;
}