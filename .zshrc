if [[ -f "/opt/homebrew/bin/brew" ]] then
  eval "$(/opt/homebrew/bin/brew shellenv)"
fi

export LS_COLORS="$(vivid generate catppuccin-mocha)"
export EDITOR='nvim'
export PATH=$PATH:$ANDROID_HOME/emulator
export PATH=$PATH:$ANDROID_HOME/platform-tools
export PATH="$HOME/bin:$PATH"
export PATH="$HOME/.local/bin:$PATH"
export MANPAGER='nvim +Man!'

# Source zsh plugins
source $(brew --prefix)/share/zsh-fast-syntax-highlighting/fast-syntax-highlighting.plugin.zsh
source $(brew --prefix)/share/zsh-autosuggestions/zsh-autosuggestions.zsh
source $(brew --prefix)/share/zsh-completions

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
source <(fzf --zsh)

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
--height=100% \
--border=none \
--cycle \
--no-scrollbar \
--preview-window=right,border-none \
--layout=reverse \
--multi"
export FZF_CTRL_T_OPTS="\
--preview 'bat -n --color=always {}'"
export FZF_ALT_C_OPTS="\
--preview 'lsd --tree --color=always {} | head -200'"
export _ZO_FZF_OPTS="\
$FZF_DEFAULT_OPTS \
--no-multi \
--no-sort \
--preview 'lsd --tree --color=always {2..} | head -200'"

eval "$(zoxide init zsh)"
eval "$(starship init zsh)"
eval "$(fnm env --use-on-cd)"

# Load completions
autoload -Uz compinit && compinit

# Function to edit current prompt (or previous one if the current is empty) in neovim
function edit-command-in-nvim {
  local tmpfile="$PWD/.zsh-edit-command-$$.zsh"
  local runflag="$PWD/.zsh-edit-command-$$.run"
  local mtime_before mtime_after
  local new_command=""
  local action="discard"  # enum: discard, load, run

  if [[ -z "$BUFFER" ]]; then
    BUFFER=$(fc -ln -1)
  fi

  {
    echo "# Temporary Zsh command buffer"
    echo "# Edit this buffer to modify your command and save to update the prompt"
    echo "# To run the command press <Enter> in normal mode"
    echo "# To load the command into your prompt after editing, save and quit (e.g., :wq)"
    echo "# To discard, quit without saving (e.g., :q)"
    echo "# Lines starting with # will be ignored"
    echo "# --------------------"
    print -r -- "$BUFFER"
  } > "$tmpfile"

  mtime_before=$(stat -f %m "$tmpfile")

  nvim \
    -c 'set filetype=zsh' \
    -c "function! SaveAndQuit()
          write!
          silent! execute '!touch $runflag'
          qa!
        endfunction" \
    -c "nnoremap <silent> <CR> :call SaveAndQuit()<CR>" \
    -c 'normal! G$' \
    "$tmpfile" > /dev/tty

  if [[ -f "$tmpfile" ]]; then
    mtime_after=$(stat -f %m "$tmpfile")

    if (( mtime_after > mtime_before )); then
      new_command=$(grep -v '^#' "$tmpfile")
      BUFFER="$new_command"
      CURSOR=${#BUFFER}
      if [[ -f "$runflag" ]]; then
        action="run"
      else
        action="load"
      fi
    fi
  fi

  rm -f "$tmpfile" "$runflag"

  case "$action" in
    run)
      zle accept-line
      ;;
    load)
      zle redisplay
      ;;
    discard|*)
      BUFFER=""
      CURSOR=0
      zle redisplay
      ;;
  esac
}
zle -N edit-command-in-nvim

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

# Aliases
alias gg='lazygit'
alias ls='lsd'
alias l='lsd -lAh'
alias vim="nvim"
alias v="nvim"
alias cat="bat"
alias g="git"
alias man='MANWIDTH=$((COLUMNS > 80 ? 80 : COLUMNS)) man'

# Keymaps
bindkey "^[e" edit-command-in-nvim
bindkey "^E" end-of-line
bindkey "^Z" vim-ctrl-z
bindkey "^F" forward-word
bindkey "^N" history-search-forward
bindkey "^P" history-search-backward
bindkey -r '\e'

[[ $- != *i* ]] && return

if command -v tmux >/dev/null 2>&1 && [[ -z "$TMUX" ]]; then
  tmux a || tmux
fi
