#ifndef AUDIO_H
#define AUDIO_H
namespace nim {
    class Audio {
    public:
        virtual void Init() = 0;
        virtual void Quit() = 0;
    };
}// namespace nim
#endif//AUDIO_H