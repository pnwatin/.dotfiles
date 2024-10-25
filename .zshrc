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
export PATH=$PATH:$ANDROID_HOME/emulator
export PATH=$PATH:$ANDROID_HOME/platform-tools
export PATH="$HOME/bin:$PATH"

# Add in zsh plugins
zinit light zdharma-continuum/fast-syntax-highlighting
zinit light zsh-users/zsh-completions
zinit light zsh-users/zsh-autosuggestions

# Add in snippets
zinit snippet OMZP::gitfast
zinit snippet OMZP::git-auto-fetch

# Load completions
autoload -Uz compinit && compinit

zinit cdreplay -q

# History
HISTSIZE=10000
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
type starship_zle-keymap-select >/dev/null || eval "$(starship init zsh)"
eval "$(fnm env --use-on-cd)"
source <(fzf --zsh)

# Function to suspend vim
function vim-ctrl-z () {
  if [[ $#BUFFER -eq 0 ]]; then
    BUFFER="fg"
    zle accept-line -w
  else
    zle push-input -w
  fi
}
zle -N vim-ctrl-z

# Function to stop docker
function dstop() {
  docker container stop $(docker ps -aq) > /dev/null
  osascript -e 'tell application "System Events" to tell process "Docker Desktop" to click menu item "Quit Docker Desktop" of menu 1 of menu bar item "Docker Desktop" of menu bar 1' >/dev/null 2>&1
}

# Function to open any app from the terminal
function o() {
    local app="$1"
    if [[ -z "$app" ]]; then
        echo "Usage: o <Application>"
    else
        open -a "/Applications/$app.app"
    fi
}

_o_completions() {
    local apps
    apps=(${(f)"$(ls /Applications | sed 's/\.app$//')"})
    _describe 'applications' apps
}

compdef _o_completions o

# Aliases
alias gg='lazygit'
alias ls='lsd'
alias l='lsd -lAh'
alias vim="nvim"
alias v="nvim"
alias cat="bat"
alias g="git"
alias ..='cd ..'

# Keymaps
bindkey "^E" end-of-line
bindkey "^Z" vim-ctrl-z
bindkey "^F" forward-word
bindkey "^N" history-search-forward
bindkey "^P" history-search-backward

# FZF
export FZF_DEFAULT_COMMAND="fd --type f --hidden --strip-cwd-prefix --follow --exclude .git"

export FZF_CTRL_T_COMMAND="$FZF_DEFAULT_COMMAND"

export FZF_ALT_C_COMMAND="fd --type d --hidden --follow --strip-cwd-prefix --exclude .git"

export FZF_COMPLETION_TRIGGER='??'

_fzf_compgen_path() {
  fd --type f --hidden --follow --exclude ".git" . "$1"
}

_fzf_compgen_dir() {
  fd --type d --hidden --follow --exclude ".git" . "$1"
}

_fzf_comprun() {
  local command=$1
  shift

  case "$command" in
    cd)           fzf --preview 'lsd --tree --color=always {} | head -200' "$@" ;;
    export|unset) fzf --preview "eval 'echo $'{}"         "$@" ;;
    ssh)          fzf --preview 'dig {}'                   "$@" ;;
    *)            fzf --preview "bat -n --color=always {}" "$@" ;;
  esac
}

export FZF_DEFAULT_OPTS="\
--color=bg+:#313244,bg:#11111b,spinner:#f5e0dc,hl:#f38ba8 \
--color=fg:#cdd6f4,header:#f38ba8,info:#cba6f7,pointer:#f5e0dc \
--color=marker:#b4befe,fg+:#cdd6f4,prompt:#cba6f7,hl+:#f38ba8 \
--color=selected-bg:#45475a \
--multi"

export FZF_CTRL_T_OPTS="\
--preview 'bat -n --color=always {}'"
export FZF_ALT_C_OPTS="\
--preview 'lsd --tree --color=always {} | head -200'"
