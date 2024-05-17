if [[ -f "/opt/homebrew/bin/brew" ]] then
  eval "$(/opt/homebrew/bin/brew shellenv)"
fi

# Set the directory we want to store zinit and plugins
ZINIT_ROOT="${XDG_DATA_HOME:-${HOME}/.local/share}/zinit"
ZINIT_HOME="$ZINIT_ROOT/zinit.git"

# Download Zinit, if it's not there yet
if [ ! -d "$ZINIT_HOME" ]; then
   mkdir -p "$(dirname $ZINIT_HOME)"
   git clone https://github.com/zdharma-continuum/zinit.git "$ZINIT_HOME"
fi

# Source/Load zinit
source "${ZINIT_HOME}/zinit.zsh"

export LS_COLORS="$(vivid generate catppuccin-mocha)"
export EDITOR='nvim'

# Add in zsh plugins
zinit light zdharma-continuum/fast-syntax-highlighting
zinit light zsh-users/zsh-completions
zinit light zsh-users/zsh-autosuggestions
zinit light jeffreytse/zsh-vi-mode

# Add in snippets
zinit snippet OMZP::gitfast

# Load completions
autoload -Uz compinit && compinit

zinit cdreplay -q

# History
HISTSIZE=5000
HISTFILE=~/.zsh_history
SAVEHIST=$HISTSIZE
HISTDUP=erase
setopt appendhistory
setopt sharehistory
setopt hist_ignore_space
setopt hist_ignore_all_dups
setopt hist_save_no_dups
setopt hist_ignore_dups
setopt hist_find_no_dups

# Completion styling
zstyle ':completion:*' matcher-list 'm:{a-z}={A-Za-z}'
zstyle ':completion:*' list-colors "${(s.:.)LS_COLORS}"
zstyle ':completion:*' menu no

# Shell integrations
eval "$(zoxide init zsh)"
eval "$(starship init zsh)"

# zvm
ZVM_VI_HIGHLIGHT_BACKGROUND=#45475a
ZVM_VI_SURROUND_BINDKEY=s-prefix
ZVM_INSERT_MODE_CURSOR=$ZVM_CURSOR_BLINKING_BEAM
ZVM_OPPEND_MODE_CURSOR=$ZVM_CURSOR_BLINKING_UNDERLINE

# functions
ghv() {
  gh repo view --web --branch $(git rev-parse --abbrev-ref HEAD)
}

nvim() {
    if [ $# -eq 0 ]; then
        TERM=xterm-kitty command nvim .
    else
        TERM=xterm-kitty command nvim "$@"
    fi
}

dstart() {
    open -a Docker -j
}

dstop() {
  docker container stop $(docker ps -aq)
  osascript -e 'tell application "System Events" to tell process "Docker Desktop" to click menu item "Quit Docker Desktop" of menu 1 of menu bar item "Docker Desktop" of menu bar 1' >/dev/null 2>&1
}

vim-ctrl-z () {
  if [[ $#BUFFER -eq 0 ]]; then
    BUFFER="fg"
    zle accept-line -w
  else
    zle push-input -w
    zle clear-screen -w
  fi
}

# aliases
alias gg='lazygit'
alias ls='lsd'
alias l='lsd -lAh'
alias vim="nvim"
alias v="nvim"
alias cat="bat"
alias g="git"
alias c='clear'

# keymaps
zle -N vim-ctrl-z
bindkey "^E" end-of-line
bindkey "^Z" vim-ctrl-z
bindkey "^F" vi-forward-word
bindkey "^N" history-search-forward
bindkey "^P" history-search-backward
