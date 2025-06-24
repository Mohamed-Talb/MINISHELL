/*
┌────────────────────────────────────────────────────────────┐
│       Bash Heredoc Delimiter Test Cases (Simplified)       │
└────────────────────────────────────────────────────────────┘

Format:
Delimiter Syntax              | Actual Delimiter

<< $'HOME'                   | HOME
<< '$HOME'                   | $HOME
<< "$HOME"                   | /home/user
<< $"HOME"                   | HOME
<< $""HOME                   | HOME
<< "$"HOME"                  | $HOME
<< "$"kk$"ff"""              | $kk$ff
<< "$"kk$ff""'               | $kk$ff
<< "$"kk$ff'"''              | $kk$ff
<< '"$"kk$ff""'              | "$"kk$ff""
<< "$"kk$ff""                | $kk$ff
<< "$"HOME""                 | $HOME
<< "$"''HOME""               | $HOME
<< '$"HOME"'                 | $"HOME"
<< ""$"HOME"""               | HOME
<< "$"HOME""                 | $HOME
<< $"$HOME"                  | /home/user
<< "$"kk$ff""'               | $kk$ff
<< '$"HOME"'                 | $"HOME"
<< ""$"HOME"""               | HOME
*/
