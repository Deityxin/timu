Option Explicit

Dim shell
Dim commandLine
Dim exitCode
Dim i
Dim currentArg

If WScript.Arguments.Count < 1 Then
    WScript.Quit 87
End If

commandLine = ""
For i = 0 To WScript.Arguments.Count - 1
    currentArg = WScript.Arguments(i)
    If InStr(currentArg, " ") > 0 And InStr(currentArg, Chr(34)) = 0 Then
        currentArg = Chr(34) & currentArg & Chr(34)
    End If

    If i > 0 Then
        commandLine = commandLine & " "
    End If
    commandLine = commandLine & currentArg
Next

Set shell = CreateObject("WScript.Shell")
exitCode = shell.Run(commandLine, 0, True)
WScript.Quit exitCode
