export ZSH="$HOME/.oh-my-zsh"
export PROMPT_EOL_MARK=''
export EDITOR='nvim'
export LS_COLORS="$(vivid generate catppuccin-mocha)"

plugins=(git z zsh-autosuggestions vi-mode zsh-syntax-highlighting git-auto-fetch)

source $ZSH/oh-my-zsh.sh

# prompt
VI_MODE_RESET_PROMPT_ON_MODE_CHANGE=true
VI_MODE_SET_CURSOR=true
VI_MODE_CURSOR_NORMAL=2
VI_MODE_CURSOR_VISUAL=4
VI_MODE_CURSOR_INSERT=5
VI_MODE_CURSOR_OPPEND=0
MODE_INDICATOR="%F{black}"
INSERT_MODE_INDICATOR="%F{white}"
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
%B$(vi_mode_prompt_info)❯%f%b '
RPROMPT=''

# aliases
alias gg='lazygit'
alias ls='lsd'

# functions
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
zle -N vim-ctrl-z


# keymaps
bindkey "^Z" vim-ctrl-z 
bindkey "^E" end-of-line       
bindkey "^ " autosuggest-accept
KEYTIMEOUT=1

