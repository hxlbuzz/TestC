/**
 * @file assist.h
 * @Synopsis  Assist in debugging
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2013-02-21
 */

#ifndef __ASSIST_H__
#define __ASSIST_H__

/// 定义 DEBUG 开关
#ifndef DEBUG
#define DEBUG 1
#endif

/// 定义DEBUG 等级
#define BASIC_DEBUG	1
#define EXTRA_DEBUG	2
#define SUPER_DEBUG	4

/// 定义LOG 函数的宏
#if DEBUG
#define TP_LOG( format, ... ) Tp_write_to_debug_log( format, ## __VA_ARGS__ )
#else
#define TP_LOG( format, ... ) 
#endif

/// 基本返回值枚举
typedef enum _Ret
{
	RET_OK,
	RET_OOM,
	RET_STOP,
	RET_INVALID_PARAMS,
	RET_FAIL
}Ret;

/// 定义extern "C" 的宏
#ifdef __cplusplus
#define DECLS_BEGIN extern "C" {
#define DECLS_END   }
#else
#define DECLS_BEGIN
#define DECLS_END
#endif/*__cplusplus*/

#if DEBUG
/// 无返回值的函数
#define TP_RETURN_IF_FAILED(p) if(!(p)) \
	{TP_LOG("%s:%d Warning: "#p" failed.\n", \
			__func__, __LINE__); return;}

/// 有返回值的函数
#define TP_RETURN_VAL_IFFAILED(p, ret) if(!(p)) \
	{TP_LOG("%s:%d Warning: "#p" failed.\n", \
			__func__, __LINE__); return (ret);}
#else
#define TP_RETURN_IF_FAILED(p)
#define TP_RETURN_VAL_IFFAILED(p, ret)
#endif

/// 安全释放
#define TP_SAFE_FREE(p) if(p != NULL) {free(p); p = NULL;}

/// 全局函数声明
void Tp_write_to_debug_log(const char* format, ...);

#endif /*__ASSIST_H__*/
