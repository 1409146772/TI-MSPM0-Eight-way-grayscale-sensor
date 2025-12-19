# 重构 Key 模块实现长短按检测与硬件消抖

## 1. 概述
将 `key.c` 从轮询模式重构为基于定时器中断的状态机模式，实现 KEY_B1 和 KEY_B2 的独立检测。

## 2. 修改文件 `key.h`
- **新增枚举**: 
    - `KeyEvent_t`: 定义 `KEY_EVENT_SHORT_PRESS` (短按) 和 `KEY_EVENT_LONG_PRESS` (长按)。
    - `KeyId_t`: 定义 `KEY_ID_B1`, `KEY_ID_B2`。
- **新增类型**: `KeyCallback_t` 函数指针，用于接收按键事件。
- **接口更新**:
    - `void key_init(void)`: 初始化定时器和中断。
    - `void key_register_callback(KeyId_t key, KeyCallback_t cb)`: 注册回调函数。
- **移除**: 旧的 `key_scan` 函数。

## 3. 修改文件 `key.c`
- **数据结构**:
    - 定义 `KeyState_t` 枚举: `KEY_STATE_IDLE`, `KEY_STATE_DEBOUNCE`, `KEY_STATE_PRESSED`, `KEY_STATE_LONG_PRESS_HOLD`。
    - 定义 `KeyControl_t` 结构体: 保存 GPIO 端口/引脚、当前状态、时间计数器、回调函数指针。
    - 定义 `gKeyControls[]` 数组管理 KEY_B1 和 KEY_B2。
- **初始化 `key_init`**:
    - 开启 `KEY_TIMER_1_INST` 的计数器。
    - 使能 `KEY_TIMER_1_INST` 的中断 (NVIC)。
- **中断服务程序 `KEY_TIMER_1_INST_IRQHandler`**:
    - 假设定时器配置为 1ms 周期 (根据 LOAD_VALUE 31999 和 32MHz 时钟推断)。
    - 遍历所有按键，执行状态机逻辑：
        - **IDLE -> DEBOUNCE**: 检测到低电平，启动消抖计时。
        - **DEBOUNCE -> PRESSED**: 持续低电平达到 20ms，确认为按下，重置长按计时。
        - **PRESSED -> IDLE (短按)**: 检测到高电平，且按下时间 < 800ms，触发 `SHORT_PRESS` 事件。
        - **PRESSED -> LONG_PRESS_HOLD (长按)**: 持续低电平 >= 800ms，触发 `LONG_PRESS` 事件。
        - **LONG_PRESS_HOLD -> IDLE**: 检测到高电平，重置状态。
- **回调注册**: 实现 `key_register_callback` 函数。

## 4. 单元测试与验证
- 创建 `key_test.c` (可选或作为注释示例)，模拟 GPIO 状态变化并调用中断处理函数，验证状态流转和回调触发。

## 5. 参数配置
- `KEY_DEBOUNCE_TIME_MS`: 20
- `KEY_LONG_PRESS_TIME_MS`: 800
- 均通过宏定义在 `key.c` 头部，方便调整。
