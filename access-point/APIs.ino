int ledControl(String command)
{

    // Get state from command
    int state = command.toInt();

    digitalWrite(2, state);
    return 1;
}

int changePW(String command)
{
    if (command.length() >= 8)
    {
        // Serial.println(command);
        writeString(passwordAddr, command);
        // Add a trigger to reset AP
    }
    return 1;
}

int scoreHome(String command)
{
    String protocolCmd = strSplit(command, '-', 0);
    String protocolVal = strSplit(command, '-', 1);

    if (stringIsNumeric(protocolVal))
    {
        int team = 0;
        scoreController(protocolCmd, protocolVal, team);
        setDigit(home, team);
    }

    return 1;
}

int scoreAway(String command)
{
    String protocolCmd = strSplit(command, '-', 0);
    String protocolVal = strSplit(command, '-', 1);

    if (stringIsNumeric(protocolVal))
    {
        int team = 1;
        scoreController(protocolCmd, protocolVal, team);
        setDigit(away, team);
    }

    return 1;
}

int clockHandler(String command)
{
    return 1;
}