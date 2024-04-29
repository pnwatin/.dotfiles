export ZSH="$HOME/.oh-my-zsh"
export PROMPT_EOL_MARK=''
export EDITOR='nvim'
export LS_COLORS="$(vivid generate catppuccin-mocha)"

plugins=(gitfast z zsh-autosuggestions zsh-syntax-highlighting git-auto-fetch zsh-vi-mode)

source $ZSH/oh-my-zsh.sh

# ZVM
ZVM_VI_HIGHLIGHT_BACKGROUND=#45475a
ZVM_VI_SURROUND_BINDKEY=s-prefix

# PROMPT
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

zvm_info() {
 if [ "$ZVM_MODE" = "$ZVM_MODE_INSERT" ]; then
    echo "%F{green}❯%f"
  else
    echo "%F{red}❮%f"
  fi
}

PROMPT='$(directory) $(git_prompt_info) $(git_prompt_status)
%B$(zvm_info)%b '

RPROMPT=''

# ALIASES & FUNCTIONS
alias gg='lazygit'
alias ls='lsd'
alias l='lsd -lAh'
alias vim="nvim"
alias v="nvim"
alias cat="bat"
alias g="git"

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
bindkey "^ " vi-forward-word

function zvm_after_init() {
  zvm_bindkey viins '^ ' vi-forward-word
  zvm_bindkey viins '^E' end-of-line
}

KEYTIMEOUT=10
