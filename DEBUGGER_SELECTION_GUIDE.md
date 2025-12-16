# 🔍 디버거 선택 가이드

WoorobotSDK 개발 시 상황별 최적 디버거 선택 가이드

---

## 📋 목차

1. [디버거 비교표](#1-디버거-비교표)
2. [상황별 추천](#2-상황별-추천)
3. [각 디버거 상세 가이드](#3-각-디버거-상세-가이드)
4. [통합 디버깅 전략](#4-통합-디버깅-전략)
5. [실전 예제](#5-실전-예제)

---

## 1. 🎯 디버거 비교표

### 핵심 디버거 비교

| 디버거 | 언어 | 사용 난이도 | 기능 | 통합성 | 권장도 | 용도 |
|--------|------|------------|------|--------|--------|------|
| **GDB** | C/C++ | ⭐⭐⭐ 중 | ⭐⭐⭐⭐⭐ 최고 | ⭐⭐⭐ 보통 | ⭐⭐⭐⭐⭐ 필수 | 저수준 디버깅, 크래시 분석 |
| **VSCode Debugger** | C/C++/Python | ⭐ 쉬움 | ⭐⭐⭐⭐ 우수 | ⭐⭐⭐⭐⭐ 최고 | ⭐⭐⭐⭐⭐ 강력 추천 | 일상적 개발 |
| **ROS2 Debugger** | C++/Python | ⭐⭐ 쉬움 | ⭐⭐⭐ 보통 | ⭐⭐⭐⭐ 우수 | ⭐⭐⭐⭐ 추천 | ROS 노드 디버깅 |
| **Python pdb** | Python | ⭐⭐ 쉬움 | ⭐⭐⭐ 보통 | ⭐⭐ 낮음 | ⭐⭐⭐ 보통 | Python 스크립트 |
| **Qt Creator** | C++/Qt | ⭐⭐ 쉬움 | ⭐⭐⭐⭐ 우수 | ⭐⭐⭐⭐ 우수 | ⭐⭐⭐ 보통 | Qt GUI 앱 |
| **CMake Debugger** | CMake | ⭐⭐⭐ 어려움 | ⭐⭐ 제한적 | ⭐⭐ 낮음 | ⭐⭐ 참고용 | 빌드 시스템 |
| **rqt_console** | ROS | ⭐ 매우 쉬움 | ⭐⭐ 제한적 | ⭐⭐⭐⭐ 우수 | ⭐⭐⭐⭐ 추천 | ROS 로그 분석 |

---

## 2. 🎯 상황별 추천

### 🥇 **1순위: VSCode Debugger (통합 개발 환경)**
**언제 사용?**
- ✅ 일상적인 C++ 개발
- ✅ Python 스크립트 디버깅
- ✅ 멀티 파일 프로젝트
- ✅ 원격 개발 (Jetson Nano)
- ✅ Git 통합 필요

**장점:**
- 🎨 직관적인 GUI
- 🔄 브레이크포인트, 스텝 실행, 변수 검사 통합
- 🌐 원격 SSH 디버깅 지원
- 📦 확장 프로그램으로 기능 확장
- 🚀 빠른 설정

**단점:**
- ⚠️ 매우 복잡한 멀티프로세스 디버깅은 제한적
- ⚠️ 저수준 메모리 분석 어려움

**추천 대상:**
- 👤 대부분의 개발자 (초보~중급)
- 👤 빠른 개발 사이클 필요
- 👤 원격 개발자

---

### 🥈 **2순위: GDB (전통적 디버거)**
**언제 사용?**
- ✅ 세그멘테이션 폴트 분석
- ✅ 코어 덤프 분석
- ✅ 저수준 메모리 문제
- ✅ 멀티스레드 복잡한 동기화 문제
- ✅ VSCode로 해결 안 되는 문제

**장점:**
- 💪 가장 강력한 기능
- 🔬 메모리 직접 검사
- 🧵 스레드 상세 분석
- 📊 어셈블리 레벨 디버깅
- 🎓 업계 표준

**단점:**
- 📚 학습 곡선 높음
- ⌨️ 명령줄 기반 (GUI 없음)
- 🐌 느린 워크플로우

**추천 대상:**
- 👤 시니어 개발자
- 👤 크래시/세그폴트 디버깅
- 👤 성능 최적화 필요

---

### 🥉 **3순위: ROS2 Launch Debugger**
**언제 사용?**
- ✅ ROS 노드 간 통신 문제
- ✅ 토픽/서비스 디버깅
- ✅ 런치 파일 실행 중 디버깅
- ✅ 멀티 노드 동시 디버깅

**장점:**
- 🤖 ROS 생태계 완전 통합
- 🔄 멀티 노드 디버깅
- 📡 토픽 데이터 실시간 확인
- 🎯 ROS 특화 기능

**단점:**
- ⚠️ ROS 외부에서는 사용 불가
- ⚠️ Python 디버깅 제한적

**추천 대상:**
- 👤 ROS 개발자
- 👤 노드 간 통신 문제 해결

---

### 특수 상황

#### Qt Creator (Qt GUI 개발 시)
**언제 사용?**
- ✅ PyQt5/Qt C++ GUI 개발
- ✅ UI 이벤트 디버깅
- ✅ 시그널/슬롯 연결 문제

**추천:** `robot_control_ui.py` (PyQt5) 개발 시 매우 유용

#### Python pdb (빠른 Python 디버깅)
**언제 사용?**
- ✅ 간단한 Python 스크립트
- ✅ VSCode 없이 터미널만 있을 때
- ✅ 빠른 print 디버깅 대체

**사용법:**
```python
import pdb; pdb.set_trace()  # 브레이크포인트
```

#### rqt_console (ROS 로그 분석)
**언제 사용?**
- ✅ ROS 노드 로그 실시간 확인
- ✅ 경고/에러 필터링
- ✅ 여러 노드 로그 통합 확인

---

## 3. 📚 각 디버거 상세 가이드

### 🎨 VSCode Debugger 완벽 가이드

#### 설치 및 설정
이미 `.vscode/launch.json` 설정 완료! (이 저장소에 포함)

#### 기본 사용법
```
1. 브레이크포인트 설정: 줄 번호 옆 클릭 (빨간 점)
2. 디버깅 시작: F5
3. 스텝 실행:
   - F10: Step Over (다음 줄)
   - F11: Step Into (함수 안으로)
   - Shift+F11: Step Out (함수 밖으로)
4. 변수 검사: Variables 패널
5. 표현식 평가: Debug Console에서 입력
```

#### C++ 디버깅 예제
```cpp
// WoorobotSDK/example/cpp/main.cpp
#include "woorobot_sdk_cpp/MotorController.h"

int main() {
    MotorController controller("/dev/ttyUSB0");
    
    // 여기에 브레이크포인트 설정 (VSCode에서 F9)
    controller.initialize();
    
    // F10으로 한 줄씩 실행
    auto status = controller.getStatus();
    
    return 0;
}
```

**VSCode에서:**
1. `main.cpp` 열기
2. `controller.initialize()` 줄에 브레이크포인트
3. `Ctrl+Shift+D` (디버그 뷰)
4. "C++: Debug Current File" 선택
5. `F5` 디버깅 시작
6. `F10`으로 한 줄씩 실행하며 `status` 변수 확인

#### Python 디버깅 예제
```python
# robot_control_ui.py
import rospy
from geometry_msgs.msg import Twist

def move_robot(linear, angular):
    # 브레이크포인트 설정
    cmd_vel = Twist()
    cmd_vel.linear.x = linear
    cmd_vel.angular.z = angular
    
    # 여기서 멈춤, 변수 확인 가능
    pub.publish(cmd_vel)

if __name__ == '__main__':
    rospy.init_node('robot_controller')
    pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)
    
    # 함수 호출
    move_robot(0.2, 0.0)
```

**VSCode에서:**
1. `F9`로 브레이크포인트 설정
2. `F5` → "Python: Current File" 선택
3. 변수 `cmd_vel`, `linear`, `angular` 검사

#### 원격 디버깅 (Jetson Nano)
```bash
# 1. VSCode에서 Remote-SSH 연결
Ctrl+Shift+P → "Remote-SSH: Connect to Host"
→ user@jetson-nano-ip

# 2. 원격에서 프로젝트 열기
File → Open Folder → /path/to/woorobotsdk

# 3. 로컬과 동일하게 디버깅!
F5로 시작
```

---

### 💪 GDB 완벽 가이드

#### 설치
```bash
sudo apt install gdb
```

#### 기본 사용법
```bash
# 컴파일 시 디버그 심볼 포함
g++ -g -o my_program main.cpp

# GDB 실행
gdb ./my_program

# GDB 명령어
(gdb) break main              # main 함수에 브레이크포인트
(gdb) run                     # 프로그램 실행
(gdb) next                    # 다음 줄 (n)
(gdb) step                    # 함수 안으로 들어가기 (s)
(gdb) print variable_name     # 변수 출력 (p)
(gdb) continue                # 계속 실행 (c)
(gdb) backtrace               # 콜 스택 (bt)
(gdb) quit                    # 종료 (q)
```

#### 실전 예제: Segmentation Fault 디버깅
```cpp
// crash.cpp
#include <iostream>

int main() {
    int* ptr = nullptr;
    *ptr = 42;  // 💥 크래시!
    return 0;
}
```

```bash
# 컴파일
g++ -g -o crash crash.cpp

# GDB로 실행
gdb ./crash

(gdb) run
# 프로그램 크래시!
# Program received signal SIGSEGV, Segmentation fault.
# 0x00000000004005a7 in main () at crash.cpp:5
# 5        *ptr = 42;

(gdb) backtrace
# #0  0x00000000004005a7 in main () at crash.cpp:5

(gdb) print ptr
# $1 = (int *) 0x0  ← nullptr 확인!

(gdb) info locals
# ptr = 0x0  ← 모든 지역 변수 확인
```

#### 코어 덤프 분석
```bash
# 코어 덤프 활성화
ulimit -c unlimited

# 프로그램 실행 후 크래시 → core 파일 생성
./my_program

# 코어 덤프 분석
gdb ./my_program core

(gdb) backtrace
(gdb) frame 0  # 크래시 지점으로 이동
(gdb) list      # 크래시 지점 코드 확인
```

#### 멀티스레드 디버깅
```bash
(gdb) info threads          # 모든 스레드 목록
(gdb) thread 2              # 스레드 2로 전환
(gdb) thread apply all bt   # 모든 스레드 백트레이스
```

---

### 🤖 ROS Debugger 가이드

#### VSCode ROS 확장 설치
```bash
code --install-extension ms-iot.vscode-ros
```

#### ROS 노드 디버깅

**launch.json 설정:**
```json
{
    "name": "ROS: Launch Node",
    "type": "cppdbg",
    "request": "launch",
    "program": "${workspaceFolder}/devel/lib/happy_robo/vel_converter_sdk",
    "args": [],
    "stopAtEntry": false,
    "cwd": "${workspaceFolder}",
    "environment": [
        {
            "name": "ROS_MASTER_URI",
            "value": "http://localhost:11311"
        }
    ],
    "externalConsole": false,
    "MIMode": "gdb",
    "setupCommands": [
        {
            "description": "Enable pretty-printing for gdb",
            "text": "-enable-pretty-printing",
            "ignoreFailures": true
        }
    ]
}
```

#### roslaunch와 함께 디버깅
```bash
# 터미널 1: roscore
roscore

# 터미널 2: 디버깅할 노드를 수동 실행
gdb --args rosrun happy_robo vel_converter_sdk

(gdb) break VelConverter::cmdVelCallback
(gdb) run
```

#### ROS 토픽 디버깅
```bash
# 토픽 리스트
rostopic list

# 토픽 데이터 확인
rostopic echo /cmd_vel

# 토픽 발행 빈도
rostopic hz /cmd_vel

# 토픽 정보
rostopic info /cmd_vel
```

#### rqt_console 사용
```bash
# 설치
sudo apt install ros-melodic-rqt-console

# 실행
rqt_console
```

**기능:**
- ✅ 모든 ROS 노드 로그 통합
- ✅ ERROR/WARN/INFO/DEBUG 필터링
- ✅ 정규표현식 검색
- ✅ 로그 저장

---

### 🖼️ Qt Creator (PyQt5 디버깅)

#### PyQt5 앱 디버깅

**VSCode에서 PyQt5 디버깅:**
```json
// .vscode/launch.json
{
    "name": "Python: Robot Control UI (PyQt5)",
    "type": "python",
    "request": "launch",
    "program": "${workspaceFolder}/robot_control_ui.py",
    "console": "integratedTerminal",
    "env": {
        "QT_QPA_PLATFORM": "xcb",
        "PYTHONPATH": "/opt/ros/melodic/lib/python2.7/dist-packages"
    }
}
```

#### Qt 시그널/슬롯 디버깅
```python
# robot_control_ui.py
from PyQt5.QtCore import pyqtSignal, QObject

class RobotController(QObject):
    speed_changed = pyqtSignal(float)
    
    def set_speed(self, speed):
        # 브레이크포인트 여기
        self.speed_changed.emit(speed)
```

**디버깅 팁:**
```python
# 시그널 연결 확인
print(f"Signal connected: {self.speed_changed.receivers()}")

# 슬롯 호출 여부 확인
def on_speed_changed(self, speed):
    print(f"Speed changed to: {speed}")  # 로그
    # 실제 로직
```

---

### 🔧 CMake Debugger (빌드 문제 디버깅)

#### CMake 디버그 출력
```cmake
# CMakeLists.txt
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "Include dirs: ${INCLUDE_DIRECTORIES}")

# 변수 모두 출력
get_cmake_property(_variableNames VARIABLES)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()
```

#### 빌드 로그 분석
```bash
# Verbose 빌드
catkin_make VERBOSE=1

# 또는
cmake --build . -- VERBOSE=1
```

---

## 4. 🎯 통합 디버깅 전략

### WoorobotSDK 프로젝트 디버깅 워크플로우

```
┌─────────────────────────────────────────┐
│     1. 개발 중 (일상적)                  │
│     ↓ VSCode Debugger                   │
│     - 브레이크포인트                     │
│     - 변수 검사                          │
│     - 스텝 실행                          │
└─────────────────────────────────────────┘
                  ↓ 문제 발생
┌─────────────────────────────────────────┐
│     2. 복잡한 문제 (크래시)              │
│     ↓ GDB                               │
│     - 백트레이스                         │
│     - 코어 덤프 분석                     │
│     - 메모리 검사                        │
└─────────────────────────────────────────┘
                  ↓ ROS 관련
┌─────────────────────────────────────────┐
│     3. ROS 통신 문제                     │
│     ↓ ROS Tools                         │
│     - rostopic echo                     │
│     - rqt_console                       │
│     - rqt_graph                         │
└─────────────────────────────────────────┘
                  ↓ 멀티 노드
┌─────────────────────────────────────────┐
│     4. 멀티 노드 디버깅                  │
│     ↓ GDB + tmux                        │
│     - 각 노드별 GDB 세션                 │
│     - 동시 디버깅                        │
└─────────────────────────────────────────┘
```

### 실전 예제: vel_converter_sdk 디버깅

#### 시나리오 1: 로봇이 움직이지 않음

**1단계: ROS 토픽 확인**
```bash
# /cmd_vel 토픽 확인
rostopic echo /cmd_vel

# 메시지가 발행되는가?
# → 아니오: UI 문제
# → 예: vel_converter_sdk 문제
```

**2단계: VSCode로 노드 디버깅**
```cpp
// vel_converter_sdk.cpp
void VelConverter::cmdVelCallback(const geometry_msgs::Twist::ConstPtr& msg) {
    // 브레이크포인트 여기
    double linear_x = msg->linear.x;
    double angular_z = msg->angular.z;
    
    // 변수 확인:
    // linear_x = 0.2  ✅ 값이 들어옴
    // angular_z = 0.0 ✅
    
    // 모터 제어 함수
    sendToMotor(linear_x, angular_z);  // ← 여기서 문제?
}
```

**3단계: 시리얼 통신 확인**
```bash
# USB 연결 확인
ls -l /dev/ttyUSB0

# 권한 확인
sudo usermod -aG dialout $USER

# 시리얼 모니터
sudo cat /dev/ttyUSB0
```

**4단계: 모터 명령 디버깅**
```cpp
void VelConverter::sendToMotor(double linear, double angular) {
    // 브레이크포인트
    
    // Swerve Drive 계산
    auto [wheel_speeds, wheel_angles] = calculateSwerve(linear, angular);
    
    // 계산 값 확인
    // wheel_speeds[0] = 0.2  ✅
    // wheel_angles[0] = 0.0  ✅
    
    // 시리얼 전송
    motor_controller_.setSpeed(0, wheel_speeds[0]);  // ← 여기가 문제?
}
```

#### 시나리오 2: 세그멘테이션 폴트

**GDB로 크래시 분석:**
```bash
# GDB 실행
gdb --args rosrun happy_robo vel_converter_sdk

(gdb) run
# Program received signal SIGSEGV, Segmentation fault.
# 0x00007ffff7a1b000 in MotorController::setSpeed() from libmotor_controller.so

(gdb) backtrace
# #0  0x00007ffff7a1b000 in MotorController::setSpeed()
# #1  0x0000555555555abc in VelConverter::sendToMotor()
# #2  0x0000555555555def in VelConverter::cmdVelCallback()

(gdb) frame 1
(gdb) print motor_controller_
# $1 = (MotorController *) 0x0  ← nullptr! 초기화 안 됨!

(gdb) list
# 55    void VelConverter::sendToMotor(double linear, double angular) {
# 56        motor_controller_->setSpeed(0, 0.2);  // ← 크래시!
# 57    }
```

**원인 발견:** `motor_controller_`가 nullptr
**해결:** 생성자에서 초기화 확인

---

## 5. 💡 실전 팁 & 베스트 프랙티스

### ✅ 개발 단계별 디버거 선택

| 개발 단계 | 주 디버거 | 보조 도구 |
|---------|----------|----------|
| **초기 개발** | VSCode | GDB (크래시 시) |
| **기능 구현** | VSCode | Python pdb |
| **통합 테스트** | ROS Tools | rqt_console |
| **성능 최적화** | GDB + perf | Valgrind |
| **배포 전** | GDB (스트레스 테스트) | 로그 분석 |

### ⚡ 빠른 문제 해결 체크리스트

#### Python 코드
```
1. ✅ print() 디버깅 (가장 빠름)
2. ✅ VSCode 디버거 (브레이크포인트)
3. ✅ Python pdb (터미널만 있을 때)
4. ⚠️ 로깅 추가 (장기적)
```

#### C++ 코드
```
1. ✅ VSCode 디버거 (일반적)
2. ✅ std::cout 디버깅 (간단한 문제)
3. ✅ GDB (크래시/세그폴트)
4. ⚠️ Valgrind (메모리 누수)
```

#### ROS 노드
```
1. ✅ rostopic echo (통신 확인)
2. ✅ rqt_console (로그 확인)
3. ✅ VSCode + ROS 확장 (개발 중)
4. ✅ GDB (복잡한 문제)
```

---

## 6. 🎓 학습 경로

### 초급 개발자 (0-1년)
```
1주차: VSCode Debugger 기본
       - 브레이크포인트, 스텝 실행, 변수 검사
       
2주차: Python 디버깅
       - pdb 기본, print 디버깅
       
3주차: ROS 기본 도구
       - rostopic, rqt_console
       
4주차: VSCode 원격 디버깅
       - SSH 연결, 원격 실행
```

### 중급 개발자 (1-3년)
```
1주차: GDB 기본
       - 기본 명령어, 백트레이스
       
2주차: GDB 고급
       - 조건부 브레이크포인트, watchpoint
       
3주차: 멀티스레드 디버깅
       - 스레드 전환, 동기화 문제
       
4주차: 성능 프로파일링
       - perf, gprof
```

### 고급 개발자 (3년+)
```
1주차: 코어 덤프 분석
2주차: 어셈블리 레벨 디버깅
3주차: Valgrind, AddressSanitizer
4주차: 커널 디버깅 (고급)
```

---

## 7. 📊 최종 권장사항

### 🏆 WoorobotSDK 프로젝트 표준 디버깅 스택

```
┌─────────────────────────────────────┐
│  1️⃣ VSCode Debugger (주력)          │
│     - 일상적 개발                    │
│     - 80% 이상의 문제 해결           │
└─────────────────────────────────────┘
           ↓ 필요 시
┌─────────────────────────────────────┐
│  2️⃣ GDB (백업)                      │
│     - 크래시, 세그폴트               │
│     - 15% 정도의 복잡한 문제         │
└─────────────────────────────────────┘
           ↓ ROS 관련
┌─────────────────────────────────────┐
│  3️⃣ ROS Tools (보조)                │
│     - rostopic, rqt_console         │
│     - 5% 정도의 ROS 특화 문제        │
└─────────────────────────────────────┘
```

### 🎯 결론

**대부분의 경우:**
```
✅ VSCode Debugger 사용
✅ 설정 이미 완료됨 (.vscode/launch.json)
✅ F5만 누르면 디버깅 시작
✅ 직관적이고 빠름
```

**특수한 경우만:**
```
⚠️ GDB: 크래시, 세그폴트
⚠️ ROS Tools: 노드 간 통신 문제
⚠️ pdb: 간단한 Python 스크립트
```

---

## 8. 📚 참고 자료

### 공식 문서
- [VSCode C++ 디버깅](https://code.visualstudio.com/docs/cpp/cpp-debug)
- [VSCode Python 디버깅](https://code.visualstudio.com/docs/python/debugging)
- [GDB 매뉴얼](https://sourceware.org/gdb/documentation/)
- [ROS 디버깅 가이드](http://wiki.ros.org/roslaunch/Tutorials/Roslaunch%20Nodes%20in%20Valgrind%20or%20GDB)

### 튜토리얼
- [GDB 치트시트](https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf)
- [VSCode 디버깅 비디오](https://code.visualstudio.com/docs/introvideos/debugging)

---

## ✅ 빠른 시작

### 1분 요약

**대부분의 개발:**
```bash
# VSCode에서 프로젝트 열기
code /path/to/woorobotsdk

# 브레이크포인트 설정 (줄 번호 클릭)
# F5 누르기
# 끝!
```

**크래시 발생 시:**
```bash
gdb --args ./my_program
(gdb) run
(gdb) backtrace
(gdb) print variable_name
```

**ROS 문제 시:**
```bash
rostopic echo /cmd_vel
rqt_console
```

---

**결론: VSCode Debugger를 기본으로 사용하고, 필요 시 GDB와 ROS Tools를 보조로 활용하세요!** 🚀
