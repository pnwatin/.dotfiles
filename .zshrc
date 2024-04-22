export ZSH="$HOME/.oh-my-zsh"
export PROMPT_EOL_MARK=''
export EDITOR='nvim'
export LS_COLORS="$(vivid generate catppuccin-mocha)"

plugins=(git z zsh-autosuggestions vi-mode zsh-syntax-highlighting git-auto-fetch)

source $ZSH/oh-my-zsh.sh

# PROMPT
VI_MODE_RESET_PROMPT_ON_MODE_CHANGE=true
VI_MODE_SET_CURSOR=true
VI_MODE_CURSOR_NORMAL=2
VI_MODE_CURSOR_VISUAL=4
VI_MODE_CURSOR_INSERT=5
VI_MODE_CURSOR_OPPEND=0
MODE_INDICATOR="%F{blue}❮"
INSERT_MODE_INDICATOR="%F{green}❯"
ZSH_THEME_GIT_PROMPT_PREFIX="%F{white}on%f %F{yellow}%B "
ZSH_THEME_GIT_PROMPT_SUFFIX="%b"
ZSH_THEME_GIT_PROMPT_DIRTY="%F{red}*%f"
ZSH_THEME_GIT_PROMPT_CLEAN=""

ZSH_THEME_GIT_PROMPT_AHEAD="%F{yellow}↑%f"
ZSH_THEME_GIT_PROMPT_BEHIND="%F{green}↓%f"
ZSH_THEME_GIT_PROMPT_DIVERGED="%F{yellow}↑%f%F{red}↓%f"
ZSH_THEME_GIT_PROMPT_STASHED=" %F{magenta}$%f"
directory () {
  echo '%B%F{blue}%(5~|%-1~/../%3~|%4~)%f%b'
}
PROMPT='$(directory) $(git_prompt_info) $(git_prompt_status)
$(vi_mode_prompt_info)%f '
RPROMPT=''

# ALIASES & FUNCTIONS
alias gg='lazygit'
alias ls='lsd'
alias l='lsd -lAh'
alias vim="nvim"
alias v="nvim"
alias cat="bat"

ghv() {
  gh repo view --web --branch $(git rev-parse --abbrev-ref HEAD)
}

nvim() {
    if [ $# -eq 0 ]; then
        command nvim .
    else
        command nvim "$@"
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

# KEYBINDINGS
zle -N vim-ctrl-z
bindkey "^Z" vim-ctrl-z 
bindkey "^E" end-of-line       
bindkey "^ " autosuggest-accept

KEYTIMEOUT=10

# FZF CONFIG
eval "$(fzf --zsh)"

# use fd instead of find
export FZF_DEFAULT_COMMAND="fd --hidden --strip-cwd-prefix --exclude .git"
export FZF_CTRL_T_COMMAND="$FZF_DEFAULT_COMMAND"
export FZF_ALT_C_COMMAND="fd --type=d --hidden --strip-cwd-prefix --exclude .git"

_fzf_compgen_path() {
  fd --hidden --exclude .git . "$1"
}

_fzf_compgen_dir() {
  fd --type=d --hidden --exclude .git . "$1"
}

export FZF_CTRL_T_OPTS="--preview 'bat -n --color=always --line-range :500 {}'"

_fzf_comprun() {
  local command=$1
  shift

  case "$command" in
    cd)           fzf --preview 'lsd --tree --color=always {} | head -200' "$@" ;;
    export|unset) fzf --preview "eval 'echo $'{}"         "$@" ;;
    ssh)          fzf --preview 'dig {}'                   "$@" ;;
    *)            fzf --preview "bat -n --color=always --line-range :500 {}" "$@" ;;
  esac
}

export FZF_DEFAULT_OPTS=" \
--color=bg+:#313244,bg:#11111b,spinner:#f5e0dc,hl:#f38ba8 \
--color=fg:#cdd6f4,header:#f38ba8,info:#cba6f7,pointer:#f5e0dc \
--color=marker:#f5e0dc,fg+:#cdd6f4,prompt:#cba6f7,hl+:#f38ba8"
