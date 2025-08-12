#!/bin/bash

# 吴川话语音合成调试脚本（优化版）
# 设置环境变量并运行espeak-ng进行调试，只显示关键的声母韵母声调信息

# 设置数据路径
export ESPEAK_DATA_PATH=/Users/luotuquan/soft/phoneme/espeak-ng

# 默认文本
TEXT="你好"

# 处理命令行参数
if [ $# -gt 0 ]; then
    TEXT="$1"
fi

echo "=== 吴川话语音合成调试（优化版）==="
echo "文本: $TEXT"
echo "数据路径: $ESPEAK_DATA_PATH"
echo "================================"

# 运行优化后的调试命令，只显示关键信息
echo "🔍 音素解析过程:"
ESPEAK_DEBUG=1 ./src/espeak-ng -v wuchuan "$TEXT" 2>&1 | grep -E "(🔍|📁|🏁|🎵|声母|韵母|鼻音|擦音|塞音|处理完成|语音合成完成|INTONATION.*声调)"

echo ""
echo "✅ 调试完成！现在日志输出已经大大简化，只显示关键的声母、韵母、声调处理信息。"