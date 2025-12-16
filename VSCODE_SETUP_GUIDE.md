# 🎨 Visual Studio Code Setup Guide for WoorobotSDK

리눅스 환경에서 Visual Studio Code를 사용한 WoorobotSDK 개발 완벽 가이드

---

## 📋 목차

1. [VSCode 설치](#1-vscode-설치)
2. [필수 확장 프로그램](#2-필수-확장-프로그램)
3. [프로젝트 열기](#3-프로젝트-열기)
4. [빌드 및 실행](#4-빌드-및-실행)
5. [디버깅](#5-디버깅)
6. [단축키](#6-단축키)
7. [문제해결](#7-문제해결)

---

## 1. 🚀 VSCode 설치

### Ubuntu/Debian (Jetson Nano 포함)

#### 방법 1: 공식 .deb 패키지 (권장)
```bash
# Microsoft GPG 키 추가
wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > packages.microsoft.gpg
sudo install -D -o root -g root -m 644 packages.microsoft.gpg /etc/apt/keyrings/packages.microsoft.gpg

# VSCode 저장소 추가
sudo sh -c 'echo "deb [arch=arm64 signed-by=/etc/apt/keyrings/packages.microsoft.gpg] https://packages.microsoft.com/repos/code stable main" > /etc/apt/sources.list.d/vscode.list'

# 설치
sudo apt update
sudo apt install code
```

#### 방법 2: Snap (간단하지만 느릴 수 있음)
```bash
sudo snap install code --classic
```

#### 방법 3: VSCodium (오픈소스 대안)
```bash
sudo apt install vscodium
```

### 실행 확인
```bash
code --version
```

---

## 2. 🔌 필수 확장 프로그램

프로젝트를 열면 자동으로 권장 확장 프로그램 설치를 제안합니다.

### 자동 설치 (권장)
1. VSCode에서 프로젝트 열기
2. 우측 하단 "Install Recommended Extensions" 클릭
3. 또는: `Ctrl+Shift+P` → "Show Recommended Extensions"

### 수동 설치
```bash
# C/C++ 개발
code --install-extension ms-vscode.cpptools
code --install-extension ms-vscode.cmake-tools

# Python 개발
code --install-extension ms-python.python
code --install-extension ms-python.vscode-pylance

# ROS 개발
code --install-extension ms-iot.vscode-ros

# Git 관리
code --install-extension eamodio.gitlens

# 코드 품질
code --install-extension streetsidesoftware.code-spell-checker

# Markdown 문서
code --install-extension yzhang.markdown-all-in-one

# 원격 개발 (SSH)
code --install-extension ms-vscode-remote.remote-ssh
```

### 핵심 확장 프로그램
| 확장 프로그램 | 용도 | 필수도 |
|-------------|------|--------|
| **C/C++ Tools** | C++ IntelliSense, 디버깅 | ⭐⭐⭐ 필수 |
| **CMake Tools** | CMake 빌드 지원 | ⭐⭐⭐ 필수 |
| **Python** | Python 개발 | ⭐⭐⭐ 필수 |
| **ROS** | ROS 메시지, 런치 파일 지원 | ⭐⭐ 권장 |
| **GitLens** | Git 히스토리 시각화 | ⭐⭐ 권장 |
| **Remote SSH** | 원격 Jetson Nano 개발 | ⭐⭐ 권장 |

---

## 3. 📂 프로젝트 열기

### 로컬에서 열기
```bash
cd /path/to/woorobotsdk
code .
```

### SSH를 통해 원격 Jetson Nano 열기
1. `Ctrl+Shift+P` → "Remote-SSH: Connect to Host"
2. 호스트 추가: `user@jetson-nano-ip`
3. 비밀번호 입력
4. 연결 후 프로젝트 폴더 열기

### SSH 설정 파일 (`~/.ssh/config`)
```
Host jetson-nano
    HostName 192.168.1.100
    User your-username
    Port 22
    IdentityFile ~/.ssh/id_rsa
```

이후 `Ctrl+Shift+P` → "Remote-SSH: Connect to Host" → `jetson-nano` 선택

---

## 4. 🔨 빌드 및 실행

### 빌드 태스크 실행

#### 키보드 단축키
- **Ctrl+Shift+B**: 기본 빌드 태스크 실행 (catkin_make)

#### 명령 팔레트
1. `Ctrl+Shift+P`
2. "Tasks: Run Task" 입력
3. 원하는 태스크 선택:
   - `catkin_make: Build All` - 전체 빌드
   - `catkin_make: Clean` - 빌드 정리
   - `CMake: Configure` - CMake 설정
   - `CMake: Build` - CMake 빌드

### 터미널에서 직접 실행
`Ctrl+` ` (백틱) 또는 `Ctrl+Shift+` ` 로 터미널 열기

```bash
# WoorobotSDK 빌드
cd WoorobotSDK
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j2

# ROS 전체 빌드
cd ~/catkin_ws  # 또는 프로젝트 루트
catkin_make -j2
```

### Python 스크립트 실행
- **F5**: 현재 Python 파일 디버그 실행
- **Ctrl+F5**: 디버깅 없이 실행

---

## 5. 🐛 디버깅

### C++ 디버깅

#### 1. 브레이크포인트 설정
- 코드 줄 번호 왼쪽 클릭 (빨간 점 생성)

#### 2. 디버깅 시작
- **F5**: 디버깅 시작
- `Ctrl+Shift+D`: 디버그 뷰 열기
- 디버그 구성 선택:
  - `C++: Debug Current File` - 현재 파일 디버깅
  - `C++: WoorobotSDK Example` - SDK 예제 디버깅

#### 3. 디버깅 컨트롤
- **F5**: 계속 실행
- **F10**: 스텝 오버 (현재 줄 실행)
- **F11**: 스텝 인투 (함수 내부로)
- **Shift+F11**: 스텝 아웃 (함수 밖으로)
- **Ctrl+Shift+F5**: 재시작
- **Shift+F5**: 정지

### Python 디버깅

#### Web Control UI 디버깅
1. `Ctrl+Shift+D` (디버그 뷰)
2. "Python: Web Control UI" 선택
3. **F5** 누르기
4. 브레이크포인트에서 멈춤

#### Robot Control UI (PyQt5) 디버깅
1. "Python: Robot Control UI (PyQt5)" 선택
2. **F5** 누르기

### 변수 검사
- **Variables 패널**: 로컬 변수 확인
- **Watch 패널**: 특정 표현식 추적
- **Call Stack 패널**: 함수 호출 스택
- **Debug Console**: 실시간 표현식 평가

---

## 6. ⌨️ 단축키

### 필수 단축키

| 단축키 | 기능 |
|--------|------|
| **Ctrl+P** | 파일 빠른 열기 |
| **Ctrl+Shift+P** | 명령 팔레트 |
| **Ctrl+Shift+B** | 빌드 |
| **F5** | 디버깅 시작 |
| **Ctrl+F5** | 디버깅 없이 실행 |
| **Ctrl+Shift+F** | 전체 검색 |
| **Ctrl+Shift+H** | 전체 바꾸기 |
| **Ctrl+\`** | 터미널 토글 |
| **Ctrl+/** | 주석 토글 |
| **Ctrl+Space** | IntelliSense 트리거 |
| **F2** | 이름 변경 |
| **F12** | 정의로 이동 |
| **Shift+F12** | 참조 찾기 |
| **Ctrl+K Ctrl+F** | 선택 영역 포맷 |
| **Ctrl+Shift+I** | 문서 포맷 |

### ROS 관련 단축키

| 단축키 | 기능 |
|--------|------|
| **Ctrl+Shift+P** → "ROS: Show Status" | ROS 상태 |
| **Ctrl+Shift+P** → "ROS: Update" | ROS 환경 업데이트 |
| **Ctrl+Shift+P** → "ROS: Create Terminal" | ROS 터미널 |

---

## 7. 🛠️ 문제해결

### ❌ IntelliSense가 작동하지 않음

#### 해결 방법 1: C/C++ 구성 재설정
```bash
# 명령 팔레트 (Ctrl+Shift+P)
C/C++: Reset IntelliSense Database
```

#### 해결 방법 2: includePath 수동 추가
`.vscode/c_cpp_properties.json` 확인 및 수정:
```json
"includePath": [
    "${workspaceFolder}/**",
    "/opt/ros/melodic/include/**",
    "/usr/include/**"
]
```

#### 해결 방법 3: 컴파일러 경로 확인
```bash
which g++
# 출력: /usr/bin/g++
```

### ❌ Python 모듈을 찾을 수 없음

#### ROS Python 경로 추가
`.vscode/settings.json`:
```json
"python.autoComplete.extraPaths": [
    "/opt/ros/melodic/lib/python2.7/dist-packages",
    "/opt/ros/noetic/lib/python3/dist-packages"
]
```

#### 환경 변수 확인
```bash
echo $PYTHONPATH
# 없으면:
export PYTHONPATH=/opt/ros/melodic/lib/python2.7/dist-packages:$PYTHONPATH
```

### ❌ CMake 빌드 실패

#### CMake 재설정
```bash
cd WoorobotSDK
rm -rf build
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
```

#### CMake Tools 재설정
```bash
# 명령 팔레트
CMake: Delete Cache and Reconfigure
```

### ❌ ROS 명령어가 인식되지 않음

#### ROS 환경 소싱
터미널에서:
```bash
source /opt/ros/melodic/setup.bash
# 또는
source /opt/ros/noetic/setup.bash
```

#### 자동 소싱 설정
`~/.bashrc`에 추가:
```bash
echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
source ~/.bashrc
```

### ❌ 젯슨 나노에서 VSCode가 느림

#### 1. Swap 메모리 확인
```bash
free -h
# Swap이 0이면 설정 필요
sudo fallocate -l 8G /swapfile
sudo chmod 600 /swapfile
sudo mkswap /swapfile
sudo swapon /swapfile
```

#### 2. VSCode 성능 최적화
`.vscode/settings.json`:
```json
{
    "files.watcherExclude": {
        "**/build/**": true,
        "**/devel/**": true
    },
    "search.followSymlinks": false,
    "C_Cpp.intelliSenseEngineFallback": "enabled"
}
```

#### 3. 경량 테마 사용
- `Ctrl+K Ctrl+T` → "Light+ (default light)" 선택

### ❌ 원격 SSH 연결 실패

#### SSH 키 설정 (비밀번호 없이 접속)
```bash
# 로컬에서 실행
ssh-keygen -t rsa -b 4096
ssh-copy-id user@jetson-nano-ip

# 이후 비밀번호 없이 접속 가능
ssh user@jetson-nano-ip
```

#### SSH 설정 파일 확인
`~/.ssh/config`:
```
Host jetson
    HostName 192.168.1.100
    User nvidia
    Port 22
```

---

## 8. 🎯 추천 워크플로우

### 개발 워크플로우 예시

#### 1. 프로젝트 열기
```bash
code ~/woorobotsdk
```

#### 2. 파일 편집
- `Ctrl+P` → 파일 이름 입력 → 빠른 열기
- `Ctrl+Shift+F` → 코드 검색

#### 3. 빌드
- `Ctrl+Shift+B` → 빌드

#### 4. 디버깅
- 브레이크포인트 설정
- `F5` → 디버깅 시작

#### 5. 커밋
- `Ctrl+Shift+G` → Git 뷰
- 변경사항 스테이징 (`+` 아이콘)
- 커밋 메시지 작성 → `Ctrl+Enter`

#### 6. 푸시
- 터미널: `git push origin genspark_ai_developer`

---

## 9. 📚 추가 리소스

### 공식 문서
- [VSCode 공식 문서](https://code.visualstudio.com/docs)
- [C++ 확장 프로그램](https://code.visualstudio.com/docs/languages/cpp)
- [Python 확장 프로그램](https://code.visualstudio.com/docs/python/python-tutorial)
- [원격 개발](https://code.visualstudio.com/docs/remote/ssh)

### ROS 관련
- [ROS VSCode 확장](https://github.com/ms-iot/vscode-ros)
- [ROS Wiki](http://wiki.ros.org/)

### CMake
- [CMake Tools 문서](https://github.com/microsoft/vscode-cmake-tools/tree/main/docs)

---

## 10. 🎉 빠른 시작 체크리스트

- [ ] VSCode 설치 완료
- [ ] 필수 확장 프로그램 설치 (C++, Python, ROS)
- [ ] 프로젝트 열기
- [ ] `.vscode/` 설정 확인
- [ ] `Ctrl+Shift+B`로 빌드 테스트
- [ ] `F5`로 디버깅 테스트
- [ ] 원격 SSH 설정 (Jetson Nano)
- [ ] Git 연동 확인

---

## ✅ 설정 완료!

이제 Visual Studio Code에서 WoorobotSDK를 효율적으로 개발할 수 있습니다! 🚀

**문제가 있으면:**
1. [문제해결](#7-문제해결) 섹션 확인
2. 터미널 로그 확인
3. 확장 프로그램 재시작 (`Ctrl+Shift+P` → "Reload Window")

**Happy Coding! 🎨**
