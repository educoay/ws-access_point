void writeString(char address, String data)
{
    int _size = data.length();
    int i;
    for (i = 0; i < _size; i++)
    {
        EEPROM.write(address + i, data[i]);
    }
    EEPROM.write(address + _size, '\0'); //Add termination null character for String Data
    EEPROM.commit();
}

String read_String(char address)
{
    int i;
    char data[100]; //Max 100 Bytes
    int len = 0;
    unsigned char k;
    k = EEPROM.read(address);
    while (k != '\0' && len < 500) //Read until null character
    {
        k = EEPROM.read(address + len);
        data[len] = k;
        len++;
    }
    data[len] = '\0';
    return String(data);
}

boolean stringIsNumeric(String strData)
{
    for (byte index = 0; index < strData.length(); index++)
    {
        if (!isDigit(strData.charAt(index)) || strData.charAt(index) == ' ' || strData.charAt(index) == '+' || strData.charAt(index) == '-' || strData.charAt(index) == '.')
        {
            return false;
            break;
        }
    }
    return true;
}

String strSplit(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++)
    {
        if (data.charAt(i) == separator || i == maxIndex)
        {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i + 1 : i;
        }
    }

    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void scoreController(String protCmd, String protValue, int team)
{
    int intProtValue = protValue.toInt();

    if (protCmd == "plus")
    {
        if (team == 0)
        {
            home += intProtValue;
        }
        else if (team == 1)
        {
            away += intProtValue;
        }
    }
    else if (protCmd == "minus")
    {
        if (team == 0)
        {
            home -= intProtValue;
        }
        else if (team == 1)
        {
            away -= intProtValue;
        }
    }
    else if (protCmd == "set")
    {
        if (team == 0)
        {
            home = intProtValue;
        }
        else if (team == 1)
        {
            away = intProtValue;
        }
    }

    if (away > maxScore)
    {
        away = 9;
    }
    else if (away < 0)
    {
        away = 0;
    }

    if (home > maxScore)
    {
        home = 9;
    }
    else if (home < 0)
    {
        home = 0;
    }
}

void timer()
{
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval)
    {
        previousMillis = currentMillis;

        String helper = "";
        if (minTimer > 0 && secTimer < 10)
        {
            helper = "0";
        }

        int parsedTimer = (String(minTimer) + helper + String(secTimer)).toInt();
        // int parsedTimer = (helper + String(secTimer)).toInt();

        setDigit(parsedTimer, -1);
        Serial.println(parsedTimer);
        secTimer--;
        if (secTimer < 1)
        {
            minTimer--;
            if (minTimer < 0)
            {
                minTimer = 9;
            }
            secTimer = 59;
        }
    }
}