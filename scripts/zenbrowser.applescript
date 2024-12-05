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
        set windowFound to false
        repeat with w in windows
            try
                set windowTitle to name of w
            on error
                set windowTitle to "No Title"
            end try
            try
                set windowSubrole to value of attribute "AXSubrole" of w
            on error
                set windowSubrole to "No Subrole"
            end try
            if windowSubrole is "AXStandardWindow" and windowTitle is not "Picture-in-Picture" then
                perform action "AXRaise" of w
                set value of attribute "AXMain" of w to true
                set value of attribute "AXFocused" of w to true
                set windowFound to true
                exit repeat
            else
                set value of attribute "AXMain" of w to false
                set value of attribute "AXFocused" of w to false
            end if
        end repeat
    end tell
end tell

