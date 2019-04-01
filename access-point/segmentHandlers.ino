void setDigit(int value, int team)
{
    // Upto 3 digits of validation
    int val1 = (value / 100) % 10;
    int val2 = (value / 10) % 10;
    int val3 = value % 10;

    Serial.print(val1);
    Serial.print(" ");
    Serial.print(val2);
    Serial.print(" ");
    Serial.print(val3);
    Serial.print(" ");

    // Reset to print new value
    if (team == 0)
    {
        homeDigits.setAllLow();
    }
    else if (team == 1)
    {
        awayDigits.setAllLow();
    }
    else
    {
        clockDigits.setAllLow();
    }

    if (value > 99)
    {
        showSegment(val1, 2, team); //value, which digit, team
    }

    if (value > 9)
    {
        showSegment(val2, 1, team);
    }

    showSegment(val3, 0, team);

    if (team == 0)
    {
        homeDigits.updateRegisters();
    }
    else if (team == 1)
    {
        awayDigits.updateRegisters();
    }
    else
    {
        clockDigits.updateRegisters();
    }

    // Turn off team selector
    // team = -1;
}

void showSegment(int value, int digit, int team)
{
    int arraySize;
    switch (value)
    {
    case 0:
        arraySize = sizeof(zeroDef) / sizeof(int);
        decodeSegment(zeroDef, arraySize, digit, team);
        break;
    case 1:
        arraySize = sizeof(oneDef) / sizeof(int);
        decodeSegment(oneDef, arraySize, digit, team);
        break;
    case 2:
        arraySize = sizeof(twoDef) / sizeof(int);
        decodeSegment(twoDef, arraySize, digit, team);
        break;
    case 3:
        arraySize = sizeof(threeDef) / sizeof(int);
        decodeSegment(threeDef, arraySize, digit, team);
        break;
    case 4:
        arraySize = sizeof(fourDef) / sizeof(int);
        decodeSegment(fourDef, arraySize, digit, team);
        break;
    case 5:
        arraySize = sizeof(fiveDef) / sizeof(int);
        decodeSegment(fiveDef, arraySize, digit, team);
        break;
    case 6:
        arraySize = sizeof(sixDef) / sizeof(int);
        decodeSegment(sixDef, arraySize, digit, team);
        break;
    case 7:
        arraySize = sizeof(sevenDef) / sizeof(int);
        decodeSegment(sevenDef, arraySize, digit, team);
        break;
    case 8:
        arraySize = sizeof(eightDef) / sizeof(int);
        decodeSegment(eightDef, arraySize, digit, team);
        break;
    case 9:
        arraySize = sizeof(nineDef) / sizeof(int);
        decodeSegment(nineDef, arraySize, digit, team);
        break;
    }
}

void decodeSegment(int segmentDefinition[], int arrSize, int digit, int team)
{
    for (int index = 0; index < arrSize; index++)
    {
        int segmentSelector = segmentDefinition[index];

        if (digit == 2)
        {
            segmentSelector += 14;
        }
        else if (digit == 1)
        {
            segmentSelector += 7;
        }

        if (team == 0)
        {
            homeDigits.set(segmentSelector, HIGH);
        }
        else if (team == 1)
        {
            awayDigits.set(segmentSelector, HIGH);
        }
        else
        {
            clockDigits.set(segmentSelector, HIGH);
        }
    }
}
