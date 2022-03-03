#include "InformationProxy.hpp"

void InformationProxy::step() {
    _nixieController->setNixieValues(_providers[_currentProvider]->getValues());
}

void InformationProxy::setProvider(int providerId) {
    _currentProvider = (providerId < 4) ? providerId : 0;
}

InformationProxy::InformationProxy(NixieController *controller) {
    _nixieController = controller;
    _currentProvider = 0;
    _providers[0] = new TimeProvider();
    _providers[1] = new DateProvider();
    _providers[2] = new YearProvider();
    _providers[3] = new CathodePoisoningPreventionProvider();
}

void InformationProxy::toggleNixiePower() {
    _nixieController->togglePowerSupply();
}

void InformationProxy::nextProvider() {
    Serial.println("Increasing Provider");
    int nextProviderIndex = (_currentProvider < 2) ? _currentProvider + 1 : 0;
    setProvider(nextProviderIndex);
}

InformationProxy::~InformationProxy() {
    delete _providers[0];
    delete _providers[1];
    delete _providers[2];
    delete _providers[3];
}

void InformationProxy::toggleNixiePoison() {
    setProvider(3);
}
