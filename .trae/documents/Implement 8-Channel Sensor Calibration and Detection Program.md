我将通过修改 `empty.c`、`key.c` 和 `data_process.c` 来实现八路灰度传感器的校准程序。

**主要修改内容：**

1. **系统时基 (`key.c`,** **`key.h`)**:

   * 在 `key.c` 中添加全局毫秒计数器 `g_system_tick`，并在现有的定时器中断 `KEY_TIMER_1_INST_IRQHandler` 中进行累加。

   * 在 `key.h` 中提供 `key_get_tick()` 接口，为 LED 闪烁和逻辑控制提供统一的时间基准。

2. **数据处理 (`data_process.c`)**:

   * 屏蔽 `process_avg_and_restart_timer` 函数中的 `printf` 打印语句，避免串口阻塞影响系统的实时性。

3. **主程序逻辑 (`empty.c`)**:

   * **状态机设计**: 定义系统状态枚举 `SystemState_t`，包含：正常模式 (`STATE_NORMAL`)、采集黑色基准 (`STATE_CALIB_BLACK`)、采集白色基准 (`STATE_CALIB_WHITE`)。

   * **全局变量**: 新增 `white_threshold[8]`（白阈值）、`black_threshold[8]`（黑阈值）、`black_val[8]`（黑基准）、`white_val[8]`（白基准）等数组。

   * **参数存储**: 利用现有的 EEPROM Type B 驱动，实现参数的读取 `load_parameters()` 和保存 `save_parameters()`。

     * 存储 ID 0-7: 对应 8 个通道的黑阈值。

     * 存储 ID 8-15: 对应 8 个通道的白阈值。

   * **按键交互 (`on_key_b1_event`)**:

     * **长按**: 系统进入 `STATE_CALIB_BLACK` 状态，LED 开始闪烁。

     * **短按**:

       * 若在 `STATE_CALIB_BLACK`: 记录当前 ADC 平均值作为黑色基准，切换至 `STATE_CALIB_WHITE`。

       * 若在 `STATE_CALIB_WHITE`: 记录当前 ADC 平均值作为白色基准，根据公式计算冗余值和最终阈值，保存至 EEPROM，停止闪烁并返回 `STATE_NORMAL`。

   * **LED 控制逻辑**:

     * 在主循环中增加 `update_leds()` 函数。

     * **校准模式**: 基于 `key_get_tick()` 实现 500ms 周期（250ms 亮/灭）的同步闪烁。

     * **正常模式**: 实时比较 `avg[i]` 与阈值，实现迟滞比较控制（>= 白阈值亮，<= 黑阈值灭，中间保持）。

**执行步骤:**

1. 修改 `key.c` 和 `key.h`，添加系统 tick 计数功能。
2. 修改 `data_process.c`，优化打印逻辑。
3. 重构 `empty.c`，实现完整的校准流程、参数管理及实时检测逻辑。

