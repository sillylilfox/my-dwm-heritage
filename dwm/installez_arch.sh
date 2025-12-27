#!/usr/bin/env bash
set -euo pipefail
IFS=$'\n\t'

DWM_DIR="$HOME/dwm"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

info()   { echo "[INFO] $*"; }
warn()   { echo "[WARNING] $*" >&2; }
error()  { echo "[ERROR] $*" >&2; exit 1; }

backup_if_exists() {
    local target="$1"
    if [[ -e "$target" ]]; then
        local backup="${target}.bak.$(date +%s)"
        warn "Backing up $target → $backup"
        mv "$target" "$backup"
    fi
}

[[ -f "$SCRIPT_DIR/.xinitrc" ]] || error ".xinitrc not found in script directory"
[[ -f "$SCRIPT_DIR/Makefile" ]] || error "Makefile not found (are you in the dwm source directory?)"

command -v pacman >/dev/null || error "pacman not found (Arch-based system required)"

info "Installing X11 config files"

backup_if_exists "$HOME/.xinitrc"
cp "$SCRIPT_DIR/.xinitrc" "$HOME/.xinitrc"

if [[ -d "$DWM_DIR" ]]; then
    warn "$DWM_DIR already exists"
    read -rp "Overwrite existing dwm directory? [y/N] " ans
    [[ "$ans" =~ ^[Yy]$ ]] || error "Aborted by user"
    backup_if_exists "$DWM_DIR"
fi

mkdir -p "$DWM_DIR"
rsync -a --exclude='.git' "$SCRIPT_DIR/" "$DWM_DIR/"

info "Installing dependencies"
sudo pacman -S --needed --noconfirm \
    feh flameshot dmenu \
    xorg xorg-xinit \
    ttf-cascadia-code ttf-cascadia-code-nerd \
    ttf-jetbrains-mono ttf-jetbrains-mono-nerd

info "Compiling dwm"
cd "$SCRIPT_DIR"
sudo make clean install

info "Installation complete"
warn "Do NOT delete $DWM_DIR unless you know how to fix .xinitrc"
info "You can edit init.sh and .xinitrc inside $DWM_DIR if needed"

