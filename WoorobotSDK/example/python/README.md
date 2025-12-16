# Example: woorobot_sdk Python Binding

이 디렉토리는 `woorobot_sdk` C++ SDK의 Python 바인딩 예제를 포함하고 있습니다.  
Python 전용 사용자 또는 개발자 모두 이 예제를 통해 바인딩된 API를 테스트할 수 있습니다.

---

## 🛠️ 설치 및 실행 방법

### 1. 일반 사용자 (패키지 설치 후 사용)

```bash
# 의존성 설치
pip install build

# build
python -m build

# pip wheel 설치
pip install dist/woorobot_sdk_*.whl

# 프로젝트에서 사용 예시
import woorobot_sdk_python._core as w

# 예제 실행
python example/python/main.py
```

패키지 설치 후 예제 참고하여 SDK를 사용할 프로젝트에서 import 후 사용하세요.

## ❓ 자주 묻는 질문 (FAQ)  [main.py](main.py)
### Q1. ImportError: No module named 'woorobot_sdk'
pip install 을 먼저 실행했는지 확인하세요.

또는 로컬 빌드 시 build/ 디렉토리가 생성되었는지 확인하세요.

반복적으로 에러가 발생할 경우 터미널에서 python 파일을 실행해보세요.

### Q2. ModuleNotFoundError가 계속 발생해요.
example/python/main.py는 상대경로에서 실행해야 합니다