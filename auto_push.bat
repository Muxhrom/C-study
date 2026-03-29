@echo off
setlocal
chcp 65001 >nul

echo [1/3] 正在添加所有文件...
git add .

:: 获取时间并生成默认 Commit 信息，使用 powershell 避免时间字符串的空格导致闪退
for /f "delims=" %%a in ('powershell -Command "Get-Date -format 'yyyy-MM-dd HH:mm:ss'"') do set "formatted_time=%%a"
set "DEFAULT_MSG=OMEN %formatted_time%"

:: 交互输入区域
set "FINAL_MSG=%DEFAULT_MSG%"
set /p "FINAL_MSG=请输入 commit 注释 (直接回车则使用默认 %DEFAULT_MSG%): "

echo.
echo [2/3] 正在提交版本 (信息: "%FINAL_MSG%")...
git commit -m "%FINAL_MSG%"

:: 初始化错误状态变量
set "SYNC_ERROR=0"

echo.
echo [3/3] 正在推送到 GitHub...
git push
if %errorlevel% neq 0 set "SYNC_ERROR=1"

echo.
if "%SYNC_ERROR%"=="0" (
    echo [成功] 代码已成功上传到 GitHub！窗口将在 5 秒后自动关闭...
    timeout /t 5 >nul
) else (
    echo [失败] 上传过程中出现错误！请检查上方的 error 或 fatal 提示。
    pause
)