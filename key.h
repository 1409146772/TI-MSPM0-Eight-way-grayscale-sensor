#ifndef KEY_H
#define KEY_H

#include <stdint.h>

/**
 * @brief 按键ID定义
 */
typedef enum {
    KEY_ID_B1 = 0,
    KEY_ID_B2,
    KEY_ID_MAX
} KeyId_t;

/**
 * @brief 按键事件定义
 */
typedef enum {
    KEY_EVENT_SHORT_PRESS,  // 短按事件 (< 500ms)
    KEY_EVENT_LONG_PRESS    // 长按事件 (> 800ms)
} KeyEvent_t;

/**
 * @brief 按键回调函数类型
 * @param event 触发的事件类型
 */
typedef void (*KeyCallback_t)(KeyEvent_t event);

/**
 * @brief 初始化按键模块
 * 
 * 初始化定时器并开启中断，准备进行按键扫描
  */
void key_init(void);

/**
 * @brief 获取系统当前运行时间（毫秒）
 * 
 * 用于非阻塞式延时、闪烁控制等时间相关逻辑。
 */
uint32_t key_get_tick(void);

/**
 * @brief 注册按键回调函数
 */
 /* @param key_id 按键ID (KEY_ID_B1 或 KEY_ID_B2)
 * @param cb 回调函数指针
 */
void key_register_callback(KeyId_t key_id, KeyCallback_t cb);

#endif /* KEY_H */
