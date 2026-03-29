@echo off
chcp 65001 >nul

echo 正在从 GitHub 拉取最新代码...
git pull

if %errorlevel% neq 0 (
    echo.
    echo [失败] 拉取出现错误！请检查网络，或是否出现了代码冲突。
    pause
) else (
    echo.
    echo [成功] 本地代码已更新至最新！窗口将在 3 秒后关闭...
    timeout /t 3 >nul
)