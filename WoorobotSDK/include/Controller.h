#pragma once

#include <chrono>
#include <iomanip>

#include "../woorobot_sdk_cpp/BoardConfig.h"
#include "../woorobot_sdk_cpp/Firmware.h"
#include "../woorobot_sdk_cpp/MainCommConfig.h"
#include "../woorobot_sdk_cpp/MotorConfig.h"
#include "../woorobot_sdk_cpp/MotorParam.h"
#include "../woorobot_sdk_cpp/MotorGain.h"
#include "../woorobot_sdk_cpp/MotorLimit.h"
#include "../woorobot_sdk_cpp/MotorControl.h"
#include "../woorobot_sdk_cpp/MotorStatus.h"

class SerialPortConnector;

class Controller {
public:
    Controller(uint8_t id, SerialPortConnector* serial_port_connector);
    ~Controller() {
        delete_ptr();
    };

	void getTimevalNow(struct timeval* tv) {
		using namespace std::chrono;
		auto now = system_clock::now();
		auto secs = time_point_cast<seconds>(now);
		auto usecs = time_point_cast<microseconds>(now) - time_point_cast<microseconds>(secs);

		tv->tv_sec  = static_cast<long>(secs.time_since_epoch().count());
		tv->tv_usec = static_cast<long>(usecs.count());
	}

    uint8_t getId();
    std::vector<uint8_t> request(std::vector<uint8_t> request, std::string description);
    std::vector<uint8_t> requestWithoutResponse(std::vector<uint8_t> request, std::string description);
	void requestAll(std::vector<uint8_t> requests);

    std::vector<uint8_t> makeRequest(std::vector<uint8_t> request);

    std::vector<uint8_t> addCRC16Modbus(std::vector<uint8_t>& data);

    bool isCrcValid(const std::vector<uint8_t>& data);
    uint16_t computeCrc16(const uint8_t* data_blk, size_t data_blk_size);
    void setBaudrate(unsigned int value);
    std::string get_port_path();
	static std::string getCurrentTimeString();

    uint8_t* selectedId;

    uint8_t* error;
    float* max_voltage;				// 소수점 1자리까지 표현, 최대 6553.5 (V)
    float* min_voltage;				// 소수점 1자리까지 표현, 최대 25.5 (V)
    uint8_t* max_temperature;			// 소수점 1자리까지 표현, 최대 25.5 (℃)

    uint8_t* comm_mode;					// 0x00: 디지털 신호 제어, 0x01: RS485 (Default), 0x02: UART1(TTL: Level 5V), 0x03: CAN, 0x04: UART3, 0x05: SPI, 0x06: I2C, 0x11: RS485(TTL) + Echo
    uint8_t* watchdog;					// (bps)

	uint8_t* motor_type;				// 모터 타입 설정 (모터 종류 및 센서 조합: DC, STEP, BLDC, PMSM, 개별채널 등)
    uint8_t* motor_encoder_direction;	// 모터 회전 방향 설정 (0=엔코더 없음, 0x01~0x04=정/역방향 및 Inverse 정/역방향, 전기각 기준)
    uint16_t* motor_encoder_cpr;
    uint16_t* electronic_angle;			// 전기각
    float* gear_ratio;					// 소수점 1자리까지 표현, 최대 6553.5
    uint8_t* lead_angle_mode;
    uint8_t* force_angle;
    uint16_t* electrical_zero;
    uint8_t* hallsensor_set;

    uint8_t* d_inductance_constant;
    uint8_t* q_inductance_constant;
    uint8_t* flux_linkage_constant;
    uint16_t* resistance_constant;		// (Ω)
    uint16_t* inductance_constant;		// (mH)
    uint16_t* torque_constant;			// (Nm/A)
    uint16_t* moment_of_inertia;		// (kg·m2)
    float* rated_speed;					// 소수점 1자리까지 표현, 최대 6553.5 (RPM)
    float* rated_current;				// 소수점 1자리까지 표현, 최대 6553.5 (A)
    float* rated_voltage;				// 소수점 1자리까지 표현, 최대 25.5 (V)

    uint8_t* position_total_gain;
    uint8_t* velocity_total_gain;
    uint8_t* current_total_gain;
    uint16_t* position_p_gain;
    uint16_t* velocity_p_gain;
    uint16_t* velocity_i_gain;
    uint16_t* current_p_gain;
    uint16_t* current_i_gain;

    unsigned int* time_max;				// (ms)
    double* position_ccw_max;			// 소수점 1자리까지 표현, 최대 429,496,729.5 (°)
    double* position_cw_max;			// 소수점 1자리까지 표현, 최대 429,496,729.5 (°)
    float* velocity_ccw_max;			// 소수점 1자리까지 표현, 최대 6553.5 (RPM)
    float* velocity_cw_max;				// 소수점 1자리까지 표현, 최대 6553.5 (RPM)
    float* current_ccw_max;				// 소수점 1자리까지 표현, 최대 6553.5 (A)
    float* current_cw_max;				// 소수점 1자리까지 표현, 최대 6553.5 (A)
    float* current_limit;				// 소수점 1자리까지 표현, 최대 6553.5 (A)

    uint16_t* acc_time;					// (10ms)
    uint16_t* dec_time;					// (10ms)
    uint8_t* motion_mode;
    unsigned int* sub_target;
    unsigned int* main_target;
    uint8_t* motor_direction;			// 0x01: CCW, 0x02: CW, 0x00: 0
    uint8_t* run_mode;
    uint8_t* motor_enable;				// 0x00: Disable, 0x01: Enable
    uint8_t* motor_brake;				// 0xX0: Bracke, 0xX1: NonBrake, 0x0X: ElectricBrakeWork, 0x1X: ElectricBrakeNonWork
    uint8_t* external_brake;

    unsigned int* time_now;
    unsigned int* time_left;
    unsigned int* position_now;
    uint8_t* position_dir;
    uint16_t* velocity_now;
    uint8_t* velocity_dir;
    uint16_t* current_now;
    uint8_t* current_dir;
    uint64_t* encoder_now;
    uint8_t* encoder_dir;
    uint8_t* hallsensor_now;
    uint16_t* absolute_value_now;
	float* voltage_now;
	uint8_t* temperature_now;

    BoardConfig boardConfig;
    MainCommConfig mainCommConfig;
    MotorConfig motorConfig;
    MotorParam motorParam;
    MotorGain motorGain;
    MotorLimit motorLimit;
    MotorControl motorControl;
    MotorStatus motorStatus;
    Firmware firmware;

    SerialPortConnector* connector;

    unsigned short CrcTable[256] = { // POLYNOMIAL : 0x8005
	0x0000, 0xc0c1, 0xc181, 0x0140, 0xc301, 0x03c0, 0x0280, 0xc241,
	0xc601, 0x06c0, 0x0780, 0xc741, 0x0500, 0xc5c1, 0xc481, 0x0440,
	0xcc01, 0x0cc0, 0x0d80, 0xcd41, 0x0f00, 0xcfc1, 0xce81, 0x0e40,
	0x0a00, 0xcac1, 0xcb81, 0x0b40, 0xc901, 0x09c0, 0x0880, 0xc841,
	0xd801, 0x18c0, 0x1980, 0xd941, 0x1b00, 0xdbc1, 0xda81, 0x1a40,
	0x1e00, 0xdec1, 0xdf81, 0x1f40, 0xdd01, 0x1dc0, 0x1c80, 0xdc41,
	0x1400, 0xd4c1, 0xd581, 0x1540, 0xd701, 0x17c0, 0x1680, 0xd641,
	0xd201, 0x12c0, 0x1380, 0xd341, 0x1100, 0xd1c1, 0xd081, 0x1040,
	0xf001, 0x30c0, 0x3180, 0xf141, 0x3300, 0xf3c1, 0xf281, 0x3240,
	0x3600, 0xf6c1, 0xf781, 0x3740, 0xf501, 0x35c0, 0x3480, 0xf441,
	0x3c00, 0xfcc1, 0xfd81, 0x3d40, 0xff01, 0x3fc0, 0x3e80, 0xfe41,
	0xfa01, 0x3ac0, 0x3b80, 0xfb41, 0x3900, 0xf9c1, 0xf881, 0x3840,
	0x2800, 0xe8c1, 0xe981, 0x2940, 0xeb01, 0x2bc0, 0x2a80, 0xea41,
	0xee01, 0x2ec0, 0x2f80, 0xef41, 0x2d00, 0xedc1, 0xec81, 0x2c40,
	0xe401, 0x24c0, 0x2580, 0xe541, 0x2700, 0xe7c1, 0xe681, 0x2640,
	0x2200, 0xe2c1, 0xe381, 0x2340, 0xe101, 0x21c0, 0x2080, 0xe041,
	0xa001, 0x60c0, 0x6180, 0xa141, 0x6300, 0xa3c1, 0xa281, 0x6240,
	0x6600, 0xa6c1, 0xa781, 0x6740, 0xa501, 0x65c0, 0x6480, 0xa441,
	0x6c00, 0xacc1, 0xad81, 0x6d40, 0xaf01, 0x6fc0, 0x6e80, 0xae41,
	0xaa01, 0x6ac0, 0x6b80, 0xab41, 0x6900, 0xa9c1, 0xa881, 0x6840,
	0x7800, 0xb8c1, 0xb981, 0x7940, 0xbb01, 0x7bc0, 0x7a80, 0xba41,
	0xbe01, 0x7ec0, 0x7f80, 0xbf41, 0x7d00, 0xbdc1, 0xbc81, 0x7c40,
	0xb401, 0x74c0, 0x7580, 0xb541, 0x7700, 0xb7c1, 0xb681, 0x7640,
	0x7200, 0xb2c1, 0xb381, 0x7340, 0xb101, 0x71c0, 0x7080, 0xb041,
	0x5000, 0x90c1, 0x9181, 0x5140, 0x9301, 0x53c0, 0x5280, 0x9241,
	0x9601, 0x56c0, 0x5780, 0x9741, 0x5500, 0x95c1, 0x9481, 0x5440,
	0x9c01, 0x5cc0, 0x5d80, 0x9d41, 0x5f00, 0x9fc1, 0x9e81, 0x5e40,
	0x5a00, 0x9ac1, 0x9b81, 0x5b40, 0x9901, 0x59c0, 0x5880, 0x9841,
	0x8801, 0x48c0, 0x4980, 0x8941, 0x4b00, 0x8bc1, 0x8a81, 0x4a40,
	0x4e00, 0x8ec1, 0x8f81, 0x4f40, 0x8d01, 0x4dc0, 0x4c80, 0x8c41,
	0x4400, 0x84c1, 0x8581, 0x4540, 0x8701, 0x47c0, 0x4680, 0x8641,
	0x8201, 0x42c0, 0x4380, 0x8341, 0x4100, 0x81c1, 0x8081, 0x4040
	};

private:
    void init();
    void delete_ptr() const;
};
