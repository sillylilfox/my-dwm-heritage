#!/usr/bin/env bash

set -euo pipefail
IFS=$'\n\t'

DWM_DIR="$HOME/dwm"
KITKAT="$DWM_DIR/kitkat/kitkat"
WALLPAPER="$DWM_DIR/wallpap.jpeg"

info() { echo "[INFO] $*"; }
warn() { echo "[WARNING] $*" >&2; }

run_bg() {
    if command -v "$1" >/dev/null 2>&1 || [[ -x "$1" ]]; then
        "$@" &
    else
        warn "Command not found: $1"
    fi
}

if [[ -z "${DISPLAY:-}" ]]; then
    warn "DISPLAY not set — are you running inside X?"
fi

# Compositor here
# run_bg picom

# Monitor layout here
# if command -v xrandr >/dev/null; then
#     xrandr --output HDMI-1-0 --mode 1920x1080 --left-of eDP-1
# fi

# Wallpaper setting here
if [[ -f "$WALLPAPER" ]]; then
    run_bg feh --bg-fill "$WALLPAPER"
else
    warn "Wallpaper not found: $WALLPAPER"
fi

# ----Status bar (kitkat settings)----
if [[ -x "$KITKAT" ]]; then
    "$KITKAT" xsetroot 1 "%b|%c|%r|%h:%m|%o.%d" &
else
    warn "Kitkat isn't executable or missing: $KITKAT"
fi

# ----Add more autostart programs below(if you want so)----
# run_bg flameshot
# run_bg nm-applet

