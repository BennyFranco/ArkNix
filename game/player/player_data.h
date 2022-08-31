#ifndef PLAYER_DATA_H
#define PLAYER_DATA_H
namespace galaga {
    class PlayerData {
    public:
        static PlayerData &Instance() {
            static std::unique_ptr<PlayerData> instance{new PlayerData()};
            return *instance;
        }

    public:
        long score = 0;
    };
}// namespace galaga
#endif