#include "BoardConfig.h"
#include "SerialPortConnector.h"

BoardConfig::BoardConfig(Controller *controller) : controller(controller) {
}

void BoardConfig::init() {
    getError();
    getMaxVoltage();
    getMinVoltage();
    getMaxTemperature();
}

void BoardConfig::softwareReset() {
    std::vector<uint8_t> request = makeSoftwareResetCommand();
    controller->request(request, "Reset software");
}

void BoardConfig::locationReset() {
    std::vector<uint8_t> request = makeLocationResetCommand();
    controller->request(request, "Reset location");
}

void BoardConfig::factoryReset() {
    std::vector<uint8_t> request = makeFactoryResetCommand();
    controller->request(request, "Reset factory");
}

void BoardConfig::setId(uint8_t id) {
    std::vector<uint8_t> request = makeSetIdCommand(id);
    controller->request(request, "Set ID : " + std::to_string(id));
    *controller->selectedId = id;
}

void BoardConfig::setError(uint8_t value) {
    std::vector<uint8_t> request = makeSetErrorCommand(value);
    controller->request(request, "Set error " + std::to_string(value));
    *controller->error = value;
}

uint8_t BoardConfig::getError() {
    std::vector<uint8_t> request = makeGetErrorCommand();
    std::vector<uint8_t> response = controller->request(request, "Get error");
    if (response.size() == 1) {
        *controller->error = response[0];
    }
    return *controller->error;
}

void BoardConfig::setMaxVoltage(float value) {
    uint16_t intValue = static_cast<uint16_t>(value * 10);
    std::vector<uint8_t> request = makeSetMaxVoltageCommand(value);
    controller->request(request, "Set max voltage " + std::to_string(value));
    *controller->max_voltage = static_cast<float>(intValue) * 0.1;
}

float BoardConfig::getMaxVoltage() {
    std::vector<uint8_t> request = makeGetMaxVoltageCommand();
    std::vector<uint8_t> response = controller->request(request, "Get max voltage");
    if (response.size() > 1) {
        uint16_t value = (static_cast<uint16_t>(response[0]) << 8) | (static_cast<uint16_t>(response[1]));
        *controller->max_voltage = static_cast<float>(value * 0.1);
    }
    return *controller->max_voltage;
}

void BoardConfig::setMinVoltage(float value) {
    uint8_t intValue = static_cast<uint8_t>(value * 10);
    std::vector<uint8_t> request = makeSetMinVoltageCommand(value);

    controller->request(request, "Set min voltage " + std::to_string(value));
    *controller->min_voltage = static_cast<float>(intValue) * 0.1;
}

float BoardConfig::getMinVoltage() {
    std::vector<uint8_t> request = makeGetMinVoltageCommand();
    std::vector<uint8_t> response = controller->request(request, "Get min voltage");
    if (response.size() > 0) {
        *controller->min_voltage = response[0] * 0.1;
    }
    return *controller->min_voltage;
}

void BoardConfig::setMaxTemperature(uint8_t value) {
    std::vector<uint8_t> request = makeSetMaxTemperatureCommand(value);
    controller->request(request, "Set max temperature " + std::to_string(value));
    *controller->max_temperature = value;
}

uint8_t BoardConfig::getMaxTemperature() {
    std::vector<uint8_t> request = makeGetMaxTemperatureCommand();
    std::vector<uint8_t> response = controller->request(request, "Get max temperature");
    if (response.size() > 0) {
        *controller->max_temperature = response[0];
    }
    return *controller->max_temperature;
}

std::vector<uint8_t> BoardConfig::makeSoftwareResetCommand() {
    std::vector<uint8_t> request = {
        0x01, 0x00, 0x03, 0x01
    };
    return controller->makeRequest(request);
}

std::vector<uint8_t> BoardConfig::makeLocationResetCommand() {
    std::vector<uint8_t> request = {
        0x01, 0x00, 0x03, 0x02
    };
    return controller->makeRequest(request);
}

std::vector<uint8_t> BoardConfig::makeFactoryResetCommand() {
    std::vector<uint8_t> request = {
        0x01, 0x00, 0x03, 0xAB
    };
    return controller->makeRequest(request);
}

std::vector<uint8_t> BoardConfig::makeSetIdCommand(uint8_t id) {
    std::vector<uint8_t> request = {
        0x01, Address::ID, 0x03, id
    };
    return controller->makeRequest(request);
}

std::vector<uint8_t> BoardConfig::makeSetErrorCommand(uint8_t value) {
    std::vector<uint8_t> request = {
        0x01, Address::ADDRESS_ERROR, 0x03, value
    };
    return controller->makeRequest(request);
}

std::vector<uint8_t> BoardConfig::makeGetErrorCommand() {
    std::vector<uint8_t> request = {
        0x02, Address::ADDRESS_ERROR, 0x03, 0x01
    };
    return controller->makeRequest(request);
}

std::vector<uint8_t> BoardConfig::makeSetMaxVoltageCommand(float value) {
    uint16_t intValue = static_cast<uint16_t>(value * 10);
    uint8_t high = intValue >> 8;
    uint8_t low = intValue & 0xFF;

    std::vector<uint8_t> request = {
        0x01, Address::VOLTAGE_MAX, 0x04, high, low
    };
    return controller->makeRequest(request);
}

std::vector<uint8_t> BoardConfig::makeGetMaxVoltageCommand() {
    std::vector<uint8_t> request = {
        0x02, Address::VOLTAGE_MAX, 0x03, 0x02
    };
    return controller->makeRequest(request);
}

std::vector<uint8_t> BoardConfig::makeSetMinVoltageCommand(float value) {
    uint8_t intValue = static_cast<uint8_t>(value * 10);
    std::vector<uint8_t> request = {
        0x01, Address::VOLTAGE_MIN, 0x03, intValue
    };
    return controller->makeRequest(request);
}

std::vector<uint8_t> BoardConfig::makeGetMinVoltageCommand() {
    std::vector<uint8_t> request = {
        0x02, Address::VOLTAGE_MIN, 0x03, 0x01
    };
    return controller->makeRequest(request);
}

std::vector<uint8_t> BoardConfig::makeSetMaxTemperatureCommand(uint8_t value) {
    std::vector<uint8_t> request = {
        0x01, Address::TEMPERATURE_MAX, 0x03, value
    };
    return controller->makeRequest(request);
}

std::vector<uint8_t> BoardConfig::makeGetMaxTemperatureCommand() {
    std::vector<uint8_t> request = {
        0x02, Address::TEMPERATURE_MAX, 0x03, 0x01
    };
    return controller->makeRequest(request);
}

void BoardConfig::setBoardConfig(uint8_t id, uint8_t error, float maxVoltage, float minVoltage, float maxTemperature) {
    setId(id);
    setError(error);
    setMaxVoltage(maxVoltage);
    setMinVoltage(minVoltage);
    setMaxTemperature(maxTemperature);
}
