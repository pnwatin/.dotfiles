#!/bin/bash

PID_FILE="$HOME/.kanata_pids"

start() {
  echo "Starting Karabiner Virtual HID Daemon..."
  /Library/Application\ Support/org.pqrs/Karabiner-DriverKit-VirtualHIDDevice/Applications/Karabiner-VirtualHIDDevice-Daemon.app/Contents/MacOS/Karabiner-VirtualHIDDevice-Daemon >/dev/null 2>&1 &
  KARABINER_PID=$!
  sleep 1

  echo "Starting Kanata..."
  kanata --cfg ~/.config/kanata/config.kbd --quiet >/dev/null 2>&1 &
  KANATA_PID=$!
  sleep 2

  echo "$KARABINER_PID" >"$PID_FILE"
  echo "$KANATA_PID" >>"$PID_FILE"

  echo "✅ Kanata and Karabiner started!"
}

stop() {
  echo "Stopping Kanata and Karabiner..."
  while IFS= read -r pid; do
    kill "$pid" 2>/dev/null
  done <"$PID_FILE"
  rm "$PID_FILE"
  echo "🛑 Processes stopped."
}

toggle() {
  if [ -f "$PID_FILE" ]; then
    stop
  else
    start
  fi
}

toggle
