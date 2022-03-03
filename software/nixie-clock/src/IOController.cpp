#include "IOController.hpp"

#define INPUT1 36

template <typename T>
struct Callback1;

template <typename Ret, typename... Params>
struct Callback1<Ret(Params...)> {
    template <typename... Args>
    static Ret callback(Args... args) {
        return func(args...);
    }
    static std::function<Ret(Params...)> func;
};

template <typename Ret, typename... Params>
std::function<Ret(Params...)> Callback1<Ret(Params...)>::func;

template <typename T>
struct Callback2;

template <typename Ret, typename... Params>
struct Callback2<Ret(Params...)> {
    template <typename... Args>
    static Ret callback(Args... args) {
        return func(args...);
    }
    static std::function<Ret(Params...)> func;
};

template <typename Ret, typename... Params>
std::function<Ret(Params...)> Callback2<Ret(Params...)>::func;

template <typename T>
struct Callback3;

template <typename Ret, typename... Params>
struct Callback3<Ret(Params...)> {
    template <typename... Args>
    static Ret callback(Args... args) {
        return func(args...);
    }
    static std::function<Ret(Params...)> func;
};

template <typename Ret, typename... Params>
std::function<Ret(Params...)> Callback3<Ret(Params...)>::func;

void IOController::initialize() {
    Log.noticeln("Initializing I/O");
    _button = OneButton(INPUT1, true);

    Callback1<void(void)>::func = std::bind(&InformationProxy::nextProvider, &*_informationProxy);
    auto funcNextProvider = static_cast<callbackFunction>(Callback1<void(void)>::callback);
    _button.attachClick(funcNextProvider);

    Callback2<void(void)>::func = std::bind(&InformationProxy::toggleNixiePower, &*_informationProxy);
    auto funcTogglePower = static_cast<callbackFunction>(Callback2<void(void)>::callback);
    _button.attachLongPressStop(funcTogglePower);

    Callback3<void(void)>::func = std::bind(&InformationProxy::toggleNixiePoison, &*_informationProxy);
    auto funcTogglePoison = static_cast<callbackFunction>(Callback3<void(void)>::callback);
    _button.attachDoubleClick(funcTogglePoison);

}

void IOController::step() {
    _button.tick();
}

IOController::IOController(InformationProxy* proxy) : _informationProxy{proxy} {}
