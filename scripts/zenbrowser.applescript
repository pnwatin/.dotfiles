#!/usr/bin/osascript

# Required parameters:
# @raycast.schemaVersion 1
# @raycast.title ZenBrowser
# @raycast.mode silent

# Optional parameters:
# @raycast.icon 🤖

# Documentation:
# @raycast.description Open/Focus ZenBrowser ignoring PiP

tell application "Zen Browser" to activate
tell application "System Events"
    tell process "Zen Browser"
        set frontmost to true
        repeat with w in windows
            if (value of attribute "AXSubrole" of w) is "AXStandardWindow" and (name of w) is not "Picture-in-Picture" then
                perform action "AXRaise" of w
                set value of attribute "AXMain" of w to true
                set value of attribute "AXFocused" of w to true
                exit repeat
            end if
        end repeat
    end tell
end tell
